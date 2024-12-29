#include "Caravana.h"
#include "Mapa.h"
#include <iostream>
#include <cmath>

// ================== Classe Base Caravana ==================
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
    }
}

void Caravana::removerCarga(int quantidade) {
    if (cargaAtual >= quantidade) {
        cargaAtual -= quantidade;
    }
}

void Caravana::consumirAgua(int quantidade) {
    if (aguaAtual >= quantidade) {
        aguaAtual -= quantidade;
    }
}

int Caravana::calcularConsumoAguaComercio() const {
    if (tripulantes == 0) return 0;
    if (tripulantes < 10) return 1;
    return 2;
}

int Caravana::calcularConsumoAguaMilitar() const {
    if (tripulantes < 20) return 1;
    return 3;
}



void Caravana::adicionarTripulantes(int quantidade) {
    tripulantes += quantidade;
}

void Caravana::removerTripulantes(int quantidade) {
    tripulantes = std::max(0, tripulantes - quantidade);
}

// ================== Caravana de Comércio ==================
CaravanaComercio::CaravanaComercio(int id, int linha, int coluna)
        : Caravana(id, linha, coluna, 40, 200, 20) {}

bool CaravanaComercio::estaSemAgua() const { return aguaAtual == 0; }

bool CaravanaComercio::estaCheia() const { return cargaAtual >= capacidadeCarga; }

void CaravanaComercio::executarComportamento(Mapa& mapa) {
    // Exemplo: Mover para o primeiro item próximo
    auto item = mapa.encontrarItemProximo(linha, coluna, 2);
    if (item && !estaCheia()) {
        moverPara(item->linha, item->coluna);
        adicionarCarga(item->peso);
        mapa.removerItem(item->linha, item->coluna);
    }
    consumirAgua(2);
}

// ================== Caravana Militar ==================
CaravanaMilitar::CaravanaMilitar(int id, int linha, int coluna)
        : Caravana(id, linha, coluna, 5, 400, 15) {}

bool CaravanaMilitar::estaSemAgua() const { return aguaAtual == 0; }

bool CaravanaMilitar::estaCheia() const { return cargaAtual >= capacidadeCarga; }


void CaravanaMilitar::executarComportamento(Mapa& mapa) {
    // Localizar caravanas bárbaras próximas
    auto barbaro = mapa.encontrarCaravanaBarbaraProxima(linha, coluna, 1);
    if (barbaro) {
        int sorteioMilitar = std::rand() % (tripulantes + 1);
        int sorteioBarbara = std::rand() % (barbaro->getTripulantes() + 1);

        // Determinar vencedor
        if (sorteioMilitar >= sorteioBarbara) {
            // Militar vence
            int perdaMilitar = static_cast<int>(tripulantes * 0.2);
            int perdaBarbara = 2 * perdaMilitar;
            removerTripulantes(perdaMilitar);
            barbaro->removerTripulantes(perdaBarbara);

            if (barbaro->getTripulantes() <= 0) {
                // Barbaro destruído
                int aguaTransferida = std::min(barbaro->getAguaAtual(), capacidadeAgua - aguaAtual);
                aguaAtual += aguaTransferida;
                barbaro->consumirAgua(aguaTransferida); // Consome a água transferida
                mapa.removerCaravana(barbaro->getId());
            }
        } else {
            // Bárbaro vence
            int perdaBarbara = static_cast<int>(barbaro->getTripulantes() * 0.2);
            int perdaMilitar = 2 * perdaBarbara;
            barbaro->removerTripulantes(perdaBarbara);
            removerTripulantes(perdaMilitar);

            if (tripulantes <= 0) {
                // Militar destruído
                mapa.removerCaravana(id);
            }
        }
    }

    consumirAgua(3);
}



// ================== Caravana Secreta ==================
CaravanaSecreta::CaravanaSecreta(int id, int linha, int coluna)
        : Caravana(id, linha, coluna, 10, 100, 8) {}

bool CaravanaSecreta::estaSemAgua() const { return aguaAtual == 0; }

bool CaravanaSecreta::estaCheia() const { return cargaAtual >= capacidadeCarga; }

void CaravanaSecreta::executarComportamento(Mapa& mapa) {
    // Buscar itens no raio de 3 posições
    auto item = mapa.encontrarItemProximo(linha, coluna, 3);
    if (item && !estaCheia()) {
        // Move-se para o item, mesmo que esteja próximo de bárbaros
        moverPara(item->linha, item->coluna);
        adicionarCarga(item->peso);
        mapa.removerItem(item->linha, item->coluna);

        std::cout << "Caravana Secreta coletou um item na posição ("
                  << item->linha << ", " << item->coluna << ")." << std::endl;
    } else {
        // Movimento aleatório se nenhum item for encontrado
        auto novaPosicao = mapa.gerarMovimentoAleatorio(linha, coluna);
        moverPara(novaPosicao.first, novaPosicao.second);
    }

    // Consumir água no final do turno
    consumirAgua(1);
}


// ================== Caravana Bárbara ==================
CaravanaBarbara::CaravanaBarbara(int id, int linha, int coluna)
        : Caravana(id, linha, coluna, 0, 0, 12) {}

void CaravanaBarbara::executarComportamento(Mapa& mapa) {
    // Movimento aleatório
    auto novaPosicao = mapa.gerarMovimentoAleatorio(linha, coluna);
    moverPara(novaPosicao.first, novaPosicao.second);
}