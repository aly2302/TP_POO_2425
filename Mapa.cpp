// Mapa.cpp - Completo e otimizado
#include "Mapa.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

Mapa::Mapa(const std::string& nomeFicheiro, Buffer* buffer) : buffer(buffer) {
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        throw std::runtime_error("Erro ao abrir o ficheiro do mapa.");
    }

    try {
        // Ler dimensões do mapa
        ficheiro >> linhas >> colunas;
        ficheiro.ignore();

        // Inicializar o grid
        grid = new char[linhas * colunas];
        for (int i = 0; i < linhas; ++i) {
            std::string linha;
            std::getline(ficheiro, linha);
            if (linha.size() != static_cast<size_t>(colunas)) {
                throw std::runtime_error("Linha do grid não corresponde ao número de colunas.");
            }
            for (int j = 0; j < colunas; ++j) {
                grid[i * colunas + j] = linha[j];
            }
        }


    // Processar o grid para adicionar dados
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                char caracter = grid[i * colunas + j];

                // Verifica se o caractere é um número
                if (std::isdigit(caracter)) {
                    int id = gerarIDCaravana();  // Converte o caractere para o valor numérico
                    std::cout << "ID: " << id << std::endl;
                    // Adiciona uma caravana de comércio na posição correta
                    adicionarCaravana(std::make_unique<CaravanaComercio>(id, i, j));
                }
                // Verifica se o caractere é um '!' para caravana bárbara
                else if (caracter == '!') {
                    // Adiciona uma caravana bárbara na posição correta
                    adicionarCaravana(std::make_unique<CaravanaBarbara>(gerarIDCaravana(), i, j));
                }
            }
        }

        // Processar o grid para adicionar as caravanas para venda nas cidades
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                char caracter = grid[i * colunas + j];

                if (std::isalpha(caracter)) {
                    adicionarCidade(std::make_unique<Cidade>(std::string(1, caracter), i, j, *this));
                }
            }
        }





        // Ler parâmetros adicionais
        std::string str1;
        ficheiro >> str1 >> moedas;
        ficheiro >> str1 >> instantesEntreNovosItens;
        ficheiro >> str1 >> duracaoItem;
        ficheiro >> str1 >> maxItens;
        ficheiro >> str1 >> precoVendaMercadoria;
        ficheiro >> str1 >> precoCompraMercadoria;
        ficheiro >> str1 >> precoCaravana;
        ficheiro >> str1 >> instantesEntreNovosBarbaros;
        ficheiro >> str1 >> duracaoBarbaros;

        std::srand(std::time(nullptr)); // Inicializa o gerador de números aleatórios

        ficheiro.close();
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Erro ao ler o ficheiro: ") + e.what());
    }
}

Mapa::~Mapa() {
    delete[] grid;
}

const std::vector<std::unique_ptr<Caravana>>& Mapa::getCaravanas() const {
    return caravanas;
}

void Mapa::listarCaravanas() const {
    for (const auto& caravana : caravanas) {
        std::cout << "ID: " << caravana->getId()
                  << ", Tipo: " << caravana->getTipo()
                  << ", Posição: (" << caravana->getLinha() << ", " << caravana->getColuna() << ")"
                  << std::endl;
    }
}

void Mapa::listarCidades() const {
    for (const auto& cidade : cidades) {
        cidade->imprimirDetalhes();
    }
}

int Mapa::calcularIndice(int linha, int coluna) const {
    return linha * colunas + coluna;
}

int Mapa::getNumeroCaravanas() const {
    return caravanas.size();
}

bool Mapa::posicaoValida(int linha, int coluna) const {
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

void Mapa::atualizarGrid(int linha, int coluna, char simbolo) {
    if (!posicaoValida(linha, coluna)) {
        throw std::out_of_range("Posição inválida no mapa.");
    }
    grid[calcularIndice(linha, coluna)] = simbolo;
}

char Mapa::obterGrid(int linha, int coluna) const {
    if (!posicaoValida(linha, coluna)) {
        throw std::out_of_range("Posição inválida no mapa.");
    }
    return grid[calcularIndice(linha, coluna)];
}

void Mapa::imprimirMapa() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            // Acessa o caractere na posição (i, j) do grid
            std::cout << grid[i * colunas + j];  // Acesso direto usando a fórmula de índice
        }
        std::cout << std::endl;  // Nova linha após cada linha do grid
    }
}





bool Mapa::reduzirMoedas(int quantidade) {
    if (moedas >= quantidade) {
        moedas -= quantidade;
        return true;
    }
    return false;
}

bool Mapa::addMoedas(int quantidade) {
    if (moedas >= quantidade) {
        moedas += quantidade;
        return true;
    }
    return false;
}

void Mapa::adicionarCaravana(std::unique_ptr<Caravana> caravana) {
    if (!posicaoValida(caravana->getLinha(), caravana->getColuna())) {
        throw std::out_of_range("Posição inválida para adicionar a caravana.");
    }
    /*
    // Usar o ID da caravana como símbolo no grid
    int id = caravana->getId();

    char simbolo = (id < 10) ? '0' + id : '*'; // Simbolo para IDs > 9
    atualizarGrid(caravana->getLinha(), caravana->getColuna(), simbolo);
    */
    caravanas.push_back(std::move(caravana)); // Adiciona a caravana à lista
}


void Mapa::moverCaravana(int id, int novaLinha, int novaColuna) {
    for (auto& caravana : caravanas) {
        if (caravana->getId() == id) {
            if (!posicaoValida(novaLinha, novaColuna)) {
                throw std::out_of_range("Posição inválida para mover a caravana.");
            }

            // Limpar posição anterior no grid
            atualizarGrid(caravana->getLinha(), caravana->getColuna(), '.');

            // Atualizar posição da caravana
            caravana->moverPara(novaLinha, novaColuna);

            // Atualizar grid com o ID da caravana
            char simbolo = (id < 10) ? '0' + id : '*'; // Representar IDs menores que 10 como números
            atualizarGrid(novaLinha, novaColuna, simbolo);

            return;
        }
    }
    throw std::runtime_error("Caravana com ID não encontrada.");
}


void Mapa::adicionarCidade(std::unique_ptr<Cidade> cidade) {
    if (!posicaoValida(cidade->getLinha(), cidade->getColuna())) {
        throw std::out_of_range("Posição inválida para adicionar uma cidade.");
    }
    cidades.push_back(std::move(cidade));
}



bool Mapa::estaAdjacente(int linha1, int coluna1, int linha2, int coluna2) const {
    return (linha1 == linha2 && std::abs(coluna1 - coluna2) == 1) || // Mesma linha, colunas adjacentes
           (coluna1 == coluna2 && std::abs(linha1 - linha2) == 1);   // Mesma coluna, linhas adjacentes
}

std::vector<std::pair<int, int>> Mapa::encontrarCaravanasAdjacentes(int linha, int coluna) const {
    std::vector<std::pair<int, int>> proximas;
    for (const auto& caravana : caravanas) {
        if (estaAdjacente(caravana->getLinha(), caravana->getColuna(), linha, coluna)) {
            proximas.emplace_back(caravana->getLinha(), caravana->getColuna());
        }
    }
    return proximas;
}

int Mapa::gerarIDCaravana() {
    static int idAtual = 0;
    return ++idAtual;
}

std::pair<int, int> Mapa::gerarMovimentoAleatorio(int linha, int coluna) const {
    int movimento[] = {-1, 0, 1}; // Movement options: stay, up/down, left/right
    int novaLinha = linha + movimento[std::rand() % 3];
    int novaColuna = coluna + movimento[std::rand() % 3];
    if (posicaoValida(novaLinha, novaColuna)) {
        return {novaLinha, novaColuna};
    }
    return {linha, coluna}; // Return original position if invalid move
}

void Mapa::adicionarItem(int linha, int coluna) {
    if (itens.size() < maxItens && posicaoValida(linha, coluna)) {
        Item item{linha, coluna, 'I', duracaoItem};
        itens.push_back(item);
        std::cout << "Novo item gerado em (" << linha << ", " << coluna << ")." << std::endl;
    }
}


void Mapa::adicionarCaravanaBarbaraAleatoria() {
    int linha = std::rand() % linhas;
    int coluna = std::rand() % colunas;

    // Verificar se a posição está livre para adicionar uma caravana bárbara
    if (obterGrid(linha, coluna) == '.') {
        adicionarCaravana(std::make_unique<CaravanaBarbara>(gerarIDCaravana(), linha, coluna));
        std::cout << "Nova caravana bárbara gerada em (" << linha << ", " << coluna << ")." << std::endl;
    }
}



Item* Mapa::encontrarItemProximo(int linha, int coluna, int raio) const {
    for (auto& item : itens) {
        int distLinha = std::abs(item.linha - linha);
        int distColuna = std::abs(item.coluna - coluna);
        if (distLinha <= raio && distColuna <= raio) {
            return const_cast<Item*>(&item);
        }
    }
    return nullptr;
}

Caravana* Mapa::encontrarCaravanaBarbaraProxima(int linha, int coluna, int raio) const {
    for (const auto& caravana : caravanas) {
        int distLinha = std::abs(caravana->getLinha() - linha);
        int distColuna = std::abs(caravana->getColuna() - coluna);
        if (distLinha <= raio && distColuna <= raio && caravana->getTipo() == "Barbara") {
            return caravana.get();
        }
    }
    return nullptr;
}

void Mapa::atualizarBuffer() {
    buffer->limparBuffer();

    // Atualizar o buffer com o grid do mapa
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            buffer->moverCursor(i, j);
            buffer->escreverCaractere(obterGrid(i, j));
        }
    }

    // Adicionar informações adicionais no buffer
    buffer->moverCursor(linhas, 0);
    *buffer << "Moedas: " << moedas << "\n";
    *buffer << "Caravanas: " << caravanas.size() << "\n";
    /*
    *buffer << "Cidades: " << cidades.size() << "\n";
    */
    *buffer << "Itens: " << itens.size() << "\n";
}

void Mapa::removerItem(int linha, int coluna) {
    auto it = std::find_if(itens.begin(), itens.end(), [linha, coluna](const Item& item) {
        return item.linha == linha && item.coluna == coluna;
    });

    if (it != itens.end()) {
        itens.erase(it);
    }
}

void Mapa::removerCaravana(int id) {
    auto it = std::remove_if(caravanas.begin(), caravanas.end(), [id](const std::unique_ptr<Caravana>& caravana) {
        return caravana->getId() == id;
    });

    if (it != caravanas.end()) {
        caravanas.erase(it, caravanas.end());
    }
}

void Mapa::contratarTripulantes(int idCaravana, int quantidade) {
    // Encontrar a caravana pelo ID
    auto caravana = std::find_if(caravanas.begin(), caravanas.end(), [idCaravana](const std::unique_ptr<Caravana>& c) {
        return c->getId() == idCaravana;
    });

    if (caravana != caravanas.end()) {
        // Verificar se está em uma cidade
        bool estaEmCidade = false;
        /*
        for (const auto& cidade : cidades) {
            if (cidade.getLinha() == (*caravana)->getLinha() && cidade.getColuna() == (*caravana)->getColuna()) {
                estaEmCidade = true;
                break;
            }
        }
        */
        if (!estaEmCidade) {
            std::cout << "A caravana precisa estar em uma cidade para contratar tripulantes.\n";
            return;
        }

        // Verificar moedas e contratar tripulantes
        int custoTotal = quantidade; // 1 moeda por tripulante
        if (moedas >= custoTotal) {
            (*caravana)->adicionarTripulantes(quantidade);
            moedas -= custoTotal;
            std::cout << "Caravana " << idCaravana << " contratou " << quantidade << " tripulantes.\n";
        } else {
            std::cout << "Moedas insuficientes para contratar tripulantes.\n";
        }
    } else {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada.\n";
    }
}

void Mapa::comprarMercadoria(int idCaravana, int quantidade) {
    auto caravana = std::find_if(caravanas.begin(), caravanas.end(), [idCaravana](const std::unique_ptr<Caravana>& c) {
        return c->getId() == idCaravana;
    });

    if (caravana != caravanas.end()) {
        // Verificar se está em uma cidade
        bool estaEmCidade = false;
        /*
        for (const auto& cidade : cidades) {
            if (cidade.getLinha() == (*caravana)->getLinha() && cidade.getColuna() == (*caravana)->getColuna()) {
                estaEmCidade = true;
                break;
            }
        }
        */
        if (!estaEmCidade) {
            std::cout << "A caravana precisa estar em uma cidade para comprar mercadoria.\n";
            return;
        }

        int custoTotal = quantidade; // 1 moeda por tonelada
        if (moedas >= custoTotal && !(*caravana)->estaCheia()) {
            (*caravana)->adicionarCarga(quantidade);
            moedas -= custoTotal;
            std::cout << "Caravana " << idCaravana << " comprou " << quantidade << " toneladas de mercadoria.\n";
        } else {
            std::cout << "Moedas insuficientes ou caravana cheia.\n";
        }
    } else {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada.\n";
    }
}

void Mapa::venderMercadoria(int idCaravana) {
    auto caravana = std::find_if(caravanas.begin(), caravanas.end(), [idCaravana](const std::unique_ptr<Caravana>& c) {
        return c->getId() == idCaravana;
    });

    if (caravana != caravanas.end()) {
        // Verificar se está em uma cidade
        bool estaEmCidade = false;
        /*
        for (const auto& cidade : cidades) {
            if (cidade.getLinha() == (*caravana)->getLinha() && cidade.getColuna() == (*caravana)->getColuna()) {
                estaEmCidade = true;
                break;
            }
        }
        */
        if (!estaEmCidade) {
            std::cout << "A caravana precisa estar em uma cidade para vender mercadoria.\n";
            return;
        }

        int quantidade = (*caravana)->getCargaAtual();
        int valorVenda = quantidade * 2; // 2 moedas por tonelada
        moedas += valorVenda;
        (*caravana)->removerCarga(quantidade);

        std::cout << "Caravana " << idCaravana << " vendeu " << quantidade << " toneladas de mercadoria por " << valorVenda << " moedas.\n";
    } else {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada.\n";
    }
}

int Mapa::getMoedas() const {
    return moedas;
}

int Mapa::getPrecoCaravana()  const {
    return precoCaravana; // Return the caravan price
}


/*
void Mapa::executarSimulacao() {
    bool houveMudanca = false;

    // Movimentação automática das caravanas
    for (auto& caravana : caravanas) {
        auto posAnterior = std::make_pair(caravana->getLinha(), caravana->getColuna());
        caravana->executarComportamento(*this);
        auto posAtual = std::make_pair(caravana->getLinha(), caravana->getColuna());

        if (posAnterior != posAtual) {
            std::cout << "Caravana " << caravana->getId()
                      << " moveu-se de (" << posAnterior.first << ", " << posAnterior.second
                      << ") para (" << posAtual.first << ", " << posAtual.second << ")." << std::endl;
            houveMudanca = true;
        }
    }

    // Gerar novos itens, respeitando o limite de itens no mapa
    if (itens.size() < static_cast<size_t>(maxItens)) {
        adicionarItemAleatorio();
        houveMudanca = true;
    }

    // Gerar novas caravanas bárbaras, respeitando o intervalo configurado
    static int contadorBarbaros = 0;
    if (++contadorBarbaros >= instantesEntreNovosBarbaros) {
        adicionarCaravanaBarbaraAleatoria();
        contadorBarbaros = 0;
        houveMudanca = true;
    }

    // Atualizar o buffer apenas se houve mudanças
    if (houveMudanca) {
        atualizarBuffer();
        buffer->imprimirBuffer();
    }
}
*/

void Mapa::listagem_precos() const {
    std::cout << "Preço de Compra da Mercadoria: " << precoCompraMercadoria << std::endl;
    std::cout << "Preço de Venda da Mercadoria: " << precoVendaMercadoria << std::endl;
}