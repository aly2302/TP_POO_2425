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

        // Depuração
        std::cout << "Configuração carregada com sucesso:\n"
                  << "Linhas: " << linhas << ", Colunas: " << colunas << "\n"
                  << "Moedas: " << moedas << "\n"
                  << "Instantes entre novos itens: " << instantesEntreNovosItens << "\n"
                  << "Duração do item: " << duracaoItem << "\n"
                  << "Máximo de itens: " << maxItens << "\n"
                  << "Preço de venda: " << precoVendaMercadoria << "\n"
                  << "Preço de compra: " << precoCompraMercadoria << "\n"
                  << "Preço de caravana: " << precoCaravana << "\n"
                  << "Instantes entre bárbaros: " << instantesEntreNovosBarbaros << "\n"
                  << "Duração dos bárbaros: " << duracaoBarbaros << std::endl;

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
    if (moedas < precoCaravana) {
        throw std::runtime_error("Moedas insuficientes para criar uma nova caravana.");
    }

    if (!posicaoValida(caravana->getLinha(), caravana->getColuna())) {
        throw std::out_of_range("Posição inválida para adicionar a caravana.");
    }

    // Reduzir moedas e registrar a nova caravana
    moedas -= precoCaravana;

    char simbolo = 'C'; // Padrão: Comércio
    if (caravana->getTipo() == "Militar") {
        simbolo = 'M';
    } else if (caravana->getTipo() == "Secreta") {
        simbolo = 'S';
    }

    atualizarGrid(caravana->getLinha(), caravana->getColuna(), simbolo);
    std::cout << "Caravana do tipo " << caravana->getTipo()
              << " adicionada na posição ("
              << caravana->getLinha() << ", "
              << caravana->getColuna() << "). Moedas restantes: " << moedas << std::endl;

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

            // Definir símbolo com base no tipo da caravana
            char simbolo = 'C'; // Padrão: Comércio
            if (caravana->getTipo() == "Militar") {
                simbolo = 'M';
            } else if (caravana->getTipo() == "Secreta") {
                simbolo = 'S';
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

int Mapa::getMoedas() const {
    return moedas;
}

int Mapa::getPrecoCaravana() const {
    return precoCaravana;
}

/*
bool Mapa::simularCombate(Caravana& caravana1, Caravana& caravana2) {
    // Verifica se uma das caravanas é do tipo "Barbara"
    if (caravana1.getTipo() == "Barbara" || caravana2.getTipo() == "Barbara") {
        // Simula combate: destrói a caravana "não bárbara" ou a "bárbara"
        if (caravana1.getTipo() == "Barbara") {
            std::cout << "Caravana Bárbara atacou a Caravana ID " << caravana2.getId() << ".\n";
            return true; // Caravana2 foi destruída
        } else {
            std::cout << "Caravana Bárbara atacada pela Caravana ID " << caravana1.getId() << ".\n";
            return false; // Caravana1 foi destruída
        }
    }

    // Se ambas forem do mesmo tipo ou não forem bárbaras, não há combate.
    std::cout << "Interação sem combate entre as caravanas " << caravana1.getId()
              << " e " << caravana2.getId() << ".\n";
    return false;
}


bool Mapa::resolverCombates(int& combatesVencidos) {
    bool houveCombate = false;

    for (size_t i = 0; i < caravanas.size(); ++i) {
        for (size_t j = i + 1; j < caravanas.size(); ++j) {
            auto& caravana1 = caravanas[i];
            auto& caravana2 = caravanas[j];

            // Verifica se há uma caravana bárbara adjacente a uma do jogador
            if ((caravana1->getTipo() == "Barbara" || caravana2->getTipo() == "Barbara") &&
                estaAdjacente(caravana1->getLinha(), caravana1->getColuna(),
                              caravana2->getLinha(), caravana2->getColuna())) {
                houveCombate = true;

                // Decide o resultado do combate
                if (caravana1->getTipo() == "Barbara") {
                    if (simularCombate(*caravana2, *caravana1)) {
                        combatesVencidos++;
                        std::cout << "Caravana " << caravana2->getId() << " venceu o combate contra Bárbara "
                                  << caravana1->getId() << "!\n";
                        caravanas.erase(caravanas.begin() + i);
                        i--; // Reajusta índice após remoção
                        break; // Interrompe para evitar acessar ponteiros inválidos
                    } else {
                        std::cout << "Caravana Bárbara " << caravana1->getId() << " destruiu Caravana "
                                  << caravana2->getId() << ".\n";
                        caravanas.erase(caravanas.begin() + j);
                        j--; // Reajusta índice após remoção
                    }
                } else {
                    if (simularCombate(*caravana1, *caravana2)) {
                        combatesVencidos++;
                        std::cout << "Caravana " << caravana1->getId() << " venceu o combate contra Bárbara "
                                  << caravana2->getId() << "!\n";
                        caravanas.erase(caravanas.begin() + j);
                        j--; // Reajusta índice após remoção
                    } else {
                        std::cout << "Caravana Bárbara " << caravana2->getId() << " destruiu Caravana "
                                  << caravana1->getId() << ".\n";
                        caravanas.erase(caravanas.begin() + i);
                        i--; // Reajusta índice após remoção
                        break; // Interrompe para evitar acessar ponteiros inválidos
                    }
                }
            }
        }
    }

    return houveCombate;
}
*/


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

void Mapa::adicionarItem(const Item& item) {
    itens.push_back(item);
}

Item* Mapa::encontrarItemProximo(int linha, int coluna, int raio) const {
    for (const auto& item : itens) {
        int distLinha = std::abs(item.linha - linha);
        int distColuna = std::abs(item.coluna - coluna);
        if (distLinha <= raio && distColuna <= raio) {
            return const_cast<Item*>(&item);
        }
    }
    return nullptr;
}

std::pair<int, int> Mapa::gerarMovimentoAleatorio(int linha, int coluna) const {
    int novaLinha = linha + (std::rand() % 3 - 1);
    int novaColuna = coluna + (std::rand() % 3 - 1);
    if (posicaoValida(novaLinha, novaColuna)) {
        return {novaLinha, novaColuna};
    }
    return {linha, coluna};
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

    // Verificar interações entre caravanas na mesma posição
    for (size_t i = 0; i < caravanas.size(); ++i) {
        for (size_t j = i + 1; j < caravanas.size(); ++j) {
            if (caravanas[i]->getLinha() == caravanas[j]->getLinha() &&
                caravanas[i]->getColuna() == caravanas[j]->getColuna()) {
                std::cout << "Interação entre caravanas " << caravanas[i]->getId()
                          << " e " << caravanas[j]->getId() << " na posição ("
                          << caravanas[i]->getLinha() << ", " << caravanas[i]->getColuna() << ")." << std::endl;

                // Exemplo de regra: Militar protege Comércio
                if (caravanas[i]->getTipo() == "Militar" && caravanas[j]->getTipo() == "Comercio") {
                    std::cout << "Caravana Militar " << caravanas[i]->getId()
                              << " protegeu a Caravana de Comércio " << caravanas[j]->getId() << "." << std::endl;
                } else if (caravanas[j]->getTipo() == "Militar" && caravanas[i]->getTipo() == "Comercio") {
                    std::cout << "Caravana Militar " << caravanas[j]->getId()
                              << " protegeu a Caravana de Comércio " << caravanas[i]->getId() << "." << std::endl;
                }
            }
        }
    }

    // Exibir mapa apenas se houve mudanças
    if (houveMudanca) {
        imprimirMapa();
    }
}

