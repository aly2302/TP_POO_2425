#include "Mapa.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cmath>

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
            std::cout << grid[calcularIndice(i, j)];
        }
        std::cout << std::endl;
    }
}

bool Mapa::reduzirMoedas(int quantidade) {
    if (moedas >= quantidade) {
        moedas -= quantidade;
        return true;
    }
    return false;
}

void Mapa::adicionarCaravana(std::unique_ptr<Caravana> caravana) {
    if (!posicaoValida(caravana->getLinha(), caravana->getColuna())) {
        throw std::out_of_range("Posição inválida para adicionar a caravana.");
    }

    char simbolo = 'C'; // Padrão: Comércio
    if (caravana->getTipo() == "Militar") {
        simbolo = 'M';
    } else if (caravana->getTipo() == "Secreta") {
        simbolo = 'S';
    } else if (caravana->getTipo() == "Barbara") {
        simbolo = 'B';
    }

    atualizarGrid(caravana->getLinha(), caravana->getColuna(), simbolo);
    caravanas.push_back(std::move(caravana));
}

void Mapa::moverCaravana(int id, int novaLinha, int novaColuna) {
    for (auto& caravana : caravanas) {
        if (caravana->getId() == id) {
            if (!posicaoValida(novaLinha, novaColuna)) {
                throw std::out_of_range("Posição inválida para mover a caravana.");
            }

            // Limpar posição anterior
            atualizarGrid(caravana->getLinha(), caravana->getColuna(), '.');

            // Atualizar posição
            caravana->moverPara(novaLinha, novaColuna);

            // Atualizar grid com novo símbolo
            char simbolo = 'C'; // Padrão: Comércio
            if (caravana->getTipo() == "Militar") {
                simbolo = 'M';
            } else if (caravana->getTipo() == "Secreta") {
                simbolo = 'S';
            } else if (caravana->getTipo() == "Barbara") {
                simbolo = 'B';
            }

            atualizarGrid(novaLinha, novaColuna, simbolo);
            return;
        }
    }
    throw std::runtime_error("Caravana com ID não encontrada.");
}

void Mapa::adicionarCidade(const Cidade& cidade) {
    if (!posicaoValida(cidade.getLinha(), cidade.getColuna())) {
        throw std::out_of_range("Posição inválida para adicionar uma cidade.");
    }
    atualizarGrid(cidade.getLinha(), cidade.getColuna(), 'X'); // 'X' representa uma cidade
    cidades.push_back(cidade);
}

void Mapa::listarCidades() const {
    for (const auto& cidade : cidades) {
        cidade.imprimirDetalhes();
    }
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
    int delta[] = {-1, 0, 1}; // Movement options: stay, up/down, left/right
    int novaLinha = linha + delta[std::rand() % 3];
    int novaColuna = coluna + delta[std::rand() % 3];
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

    // Gerar novos itens se possível
    if (itens.size() < static_cast<size_t>(maxItens)) {
        int novaLinha = std::rand() % linhas;
        int novaColuna = std::rand() % colunas;
        if (obterGrid(novaLinha, novaColuna) == '.') {
            adicionarItem(novaLinha, novaColuna);
            std::cout << "Novo item gerado em (" << novaLinha << ", " << novaColuna << ")." << std::endl;
            houveMudanca = true;
        }
    }

    // Geração de caravanas bárbaras
    static int contadorBarbaros = 0;
    if (++contadorBarbaros >= instantesEntreNovosBarbaros) {
        int linha = std::rand() % linhas;
        int coluna = std::rand() % colunas;
        if (obterGrid(linha, coluna) == '.') {
            adicionarCaravana(std::make_unique<CaravanaBarbara>(gerarIDCaravana(), linha, coluna));
            std::cout << "Nova caravana bárbara gerada em (" << linha << ", " << coluna << ")." << std::endl;
            contadorBarbaros = 0;
            houveMudanca = true;
        }
    }

    // Exibir mapa apenas se houve mudanças
    if (houveMudanca) {
        imprimirMapa();
    }
}
