#include "Caravana.h"
#include "Mapa.h"
#include <stdexcept>

// Base Caravana implementation
Caravana::Caravana(int id, int linha, int coluna, int capacidadeCarga, int capacidadeAgua, int tripulantesInicial)
        : id(id), linha(linha), coluna(coluna), capacidadeCarga(capacidadeCarga), capacidadeAgua(capacidadeAgua),
          tripulantes(tripulantesInicial), aguaAtual(capacidadeAgua), cargaAtual(0) {}

int Caravana::getId() const { return id; }
int Caravana::getLinha() const { return linha; }
int Caravana::getColuna() const { return coluna; }
int Caravana::getCapacidadeCarga() const { return capacidadeCarga; }
int Caravana::getCapacidadeAgua() const { return capacidadeAgua; }
int Caravana::getTripulantes() const { return tripulantes; }
int Caravana::getAguaAtual() const { return aguaAtual; }
int Caravana::getCargaAtual() const { return cargaAtual; }

void Caravana::moverPara(int novaLinha, int novaColuna) {
    linha = novaLinha;
    coluna = novaColuna;
}

void Caravana::adicionarCarga(int quantidade) {
    if (cargaAtual + quantidade <= capacidadeCarga) {
        cargaAtual += quantidade;
    } else {
        throw std::runtime_error("Capacidade de carga excedida.");
    }
}

void Caravana::removerCarga(int quantidade) {
    if (cargaAtual - quantidade >= 0) {
        cargaAtual -= quantidade;
    } else {
        throw std::runtime_error("Carga insuficiente para remover.");
    }
}

void Caravana::consumirAgua(int quantidade) {
    if (aguaAtual - quantidade >= 0) {
        aguaAtual -= quantidade;
    } else {
        aguaAtual = 0;
        throw std::runtime_error("Sem água suficiente.");
    }
}

void Caravana::adicionarTripulantes(int quantidade) {
    tripulantes += quantidade;
}

void Caravana::removerTripulantes(int quantidade) {
    if (tripulantes - quantidade >= 0) {
        tripulantes -= quantidade;
    } else {
        throw std::runtime_error("Tripulantes insuficientes.");
    }
}

// CaravanaComercio
CaravanaComercio::CaravanaComercio(int id, int linha, int coluna)
        : Caravana(id, linha, coluna, 40, 200, 20) {}

bool CaravanaComercio::estaSemAgua() const { return aguaAtual <= 0; }
bool CaravanaComercio::estaCheia() const { return cargaAtual >= capacidadeCarga; }

void CaravanaComercio::executarComportamento(Mapa& mapa) {
    // Look for adjacent caravans
    auto proximas = mapa.encontrarCaravanasAdjacentes(linha, coluna);
    if (!proximas.empty()) {
        auto [novaLinha, novaColuna] = proximas.front();
        moverPara(novaLinha, novaColuna);
        return;
    }

    // Look for nearby items
    auto itemProximo = mapa.encontrarItemProximo(linha, coluna, 2);
    if (itemProximo) {
        moverPara(itemProximo->linha, itemProximo->coluna);
    }
}

// CaravanaMilitar
CaravanaMilitar::CaravanaMilitar(int id, int linha, int coluna)
        : Caravana(id, linha, coluna, 5, 400, 40) {}

bool CaravanaMilitar::estaSemAgua() const { return aguaAtual <= 0; }
bool CaravanaMilitar::estaCheia() const { return cargaAtual >= capacidadeCarga; }

void CaravanaMilitar::executarComportamento(Mapa& mapa) {
    auto barbaroProximo = mapa.encontrarCaravanaBarbaraProxima(linha, coluna, 6);
    if (barbaroProximo) {
        moverPara(barbaroProximo->getLinha(), barbaroProximo->getColuna());
    }
}

// CaravanaSecreta
CaravanaSecreta::CaravanaSecreta(int id, int linha, int coluna)
        : Caravana(id, linha, coluna, 20, 300, 30) {}

bool CaravanaSecreta::estaSemAgua() const { return aguaAtual <= 0; }
bool CaravanaSecreta::estaCheia() const { return cargaAtual >= capacidadeCarga; }

void CaravanaSecreta::executarComportamento(Mapa& mapa) {
    auto novaPos = mapa.gerarMovimentoAleatorio(linha, coluna);
    moverPara(novaPos.first, novaPos.second);
}

// CaravanaBarbara
CaravanaBarbara::CaravanaBarbara(int id, int linha, int coluna)
        : Caravana(id, linha, coluna, 0, 0, 10) {}

void CaravanaBarbara::executarComportamento(Mapa& mapa) {
    auto novaPos = mapa.gerarMovimentoAleatorio(linha, coluna);
    moverPara(novaPos.first, novaPos.second);
    std::cout << "Caravana Barbara " << getId() << " moveu-se para ("
              << novaPos.first << ", " << novaPos.second << ").\n";
}