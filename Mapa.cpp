#include "Mapa.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cmath>

Mapa::Mapa(const std::string& nomeFicheiro) {
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        throw std::runtime_error("Erro ao abrir o ficheiro do mapa.");
    }

    // Ler dimensões do mapa
    ficheiro >> linhas >> colunas;
    ficheiro.ignore(); // Ignorar nova linha após as dimensões

    // Inicializar o grid
    grid = new char[linhas * colunas];
    for (int i = 0; i < linhas; ++i) {
        std::string linha;
        std::getline(ficheiro, linha);
        if (linha.length() != colunas) {
            throw std::runtime_error("Erro: Linha do mapa com tamanho inválido.");
        }
        for (int j = 0; j < colunas; ++j) {
            grid[i * colunas + j] = linha[j];
        }
    }

    // Ler parâmetros adicionais
    ficheiro >> moedas;
    ficheiro >> instantesEntreNovosItens;
    ficheiro >> duracaoItem;
    ficheiro >> maxItens;
    ficheiro >> precoVendaMercadoria;
    ficheiro >> precoCompraMercadoria;
    ficheiro >> precoCaravana;
    ficheiro >> instantesEntreNovosBarbaros;
    ficheiro >> duracaoBarbaros;

    ficheiro.close();

    std::srand(std::time(nullptr)); // Inicializa o gerador de números aleatórios
}

Mapa::~Mapa() {
    delete[] grid;
}

int Mapa::calcularIndice(int linha, int coluna) const {
    return linha * colunas + coluna;
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


void Mapa::adicionarCaravana(std::unique_ptr<Caravana> caravana) {
    if (!posicaoValida(caravana->getLinha(), caravana->getColuna())) {
        throw std::out_of_range("Posição inválida para adicionar a caravana.");
    }

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
              << caravana->getColuna() << ")." << std::endl;

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

std::vector<std::pair<int, int>> Mapa::encontrarCaravanasAdjacentes(int linha, int coluna) const {
    std::vector<std::pair<int, int>> proximas;
    for (const auto& caravana : caravanas) {
        int distLinha = std::abs(caravana->getLinha() - linha);
        int distColuna = std::abs(caravana->getColuna() - coluna);
        if ((distLinha + distColuna) == 1) { // Apenas adjacência direta
            proximas.emplace_back(caravana->getLinha(), caravana->getColuna());
        }
    }
    return proximas;
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

    // Geração de novos itens
    if (itens.size() < static_cast<size_t>(maxItens)) {
        int novaLinha = std::rand() % linhas;
        int novaColuna = std::rand() % colunas;
        if (obterGrid(novaLinha, novaColuna) == '.') {
            adicionarItem({novaLinha, novaColuna, 'I'});
            atualizarGrid(novaLinha, novaColuna, 'I');
            std::cout << "Novo item gerado em (" << novaLinha << ", " << novaColuna << ")." << std::endl;
            houveMudanca = true;
        }
    }

    // Atualizar duração dos itens
    for (auto it = itens.begin(); it != itens.end();) {
        if (--duracaoItem <= 0) {
            atualizarGrid(it->linha, it->coluna, '.');
            std::cout << "Item em (" << it->linha << ", " << it->coluna << ") foi removido." << std::endl;
            it = itens.erase(it);
            houveMudanca = true;
        } else {
            ++it;
        }
    }

    // Exibir mapa apenas se houve mudanças
    if (houveMudanca) {
        imprimirMapa();
    }
}
