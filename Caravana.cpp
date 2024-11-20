// Caravana.cpp
#include "Caravana.h"
#include <iostream>
#include <cstdlib>

Caravana::Caravana(int linha, int coluna, int capacidadeCarga, int tripulacao, int agua, const std::string& tipo)
        : linha(linha), coluna(coluna), capacidadeCarga(capacidadeCarga), tripulacao(tripulacao), agua(agua), tipo(tipo), movimentoAutomatico(false), moedas(0) {}

void Caravana::mover(const std::string& direcao, Mapa* mapa) {
    int novaLinha = linha;
    int novaColuna = coluna;

    if (direcao == "D") novaColuna++;
    else if (direcao == "E") novaColuna--;
    else if (direcao == "C") novaLinha--;
    else if (direcao == "B") novaLinha++;
    else if (direcao == "CE") { novaLinha--; novaColuna--; }
    else if (direcao == "CD") { novaLinha--; novaColuna++; }
    else if (direcao == "BE") { novaLinha++; novaColuna--; }
    else if (direcao == "BD") { novaLinha++; novaColuna++; }

    moverNoMapa(mapa, novaLinha, novaColuna);
}

void Caravana::moverNoMapa(Mapa* mapa, int novaLinha, int novaColuna) {
    if (mapa->obterPosicao(novaLinha, novaColuna) == '.') {
        mapa->atualizarPosicao(linha, coluna, '.');
        linha = novaLinha;
        coluna = novaColuna;
        mapa->atualizarPosicao(linha, coluna, 'C');
    } else {
        std::cout << "Movimento inválido: posição ocupada." << std::endl;
    }
}

void Caravana::imprimirInfo() const {
    std::cout << "Tipo: " << tipo << ", Posição: (" << linha << ", " << coluna << ")";
    std::cout << ", Capacidade de Carga: " << capacidadeCarga << ", Tripulação: " << tripulacao << ", Água: " << agua << ", Moedas: " << moedas << std::endl;
}

void Caravana::executarMovimentoAutonomo(Mapa* mapa) {
    int novaColuna = coluna + 1;
    if (novaColuna < mapa->getColunas() && mapa->obterPosicao(linha, novaColuna) == '.') {
        moverNoMapa(mapa, linha, novaColuna);
    } else {
        std::cout << "Movimento automático bloqueado." << std::endl;
    }
}

void Caravana::ativarMovimentoAutomatico() {
    movimentoAutomatico = true;
}

void Caravana::desativarMovimentoAutomatico() {
    movimentoAutomatico = false;
}

bool Caravana::isMovimentoAutomatico() const {
    return movimentoAutomatico;
}

void Caravana::sofrerDano(int dano) {
    tripulacao -= dano;
    if (tripulacao < 0) {
        tripulacao = 0;
    }
}

bool Caravana::estaDestruida() const {
    return tripulacao <= 0;
}

bool Caravana::estaAdjacente(Caravana* outra) const {
    return (abs(linha - outra->getLinha()) <= 1) && (abs(coluna - outra->getColuna()) <= 1);
}

void Caravana::combater(Caravana* outra, Mapa* mapa) {
    int dano = std::rand() % 10 + 1;
    sofrerDano(dano);
    outra->sofrerDano(dano);
    std::cout << "Combate entre " << tipo << " e " << outra->getTipo() << ". Dano infligido: " << dano << std::endl;

    if (estaDestruida()) {
        std::cout << "A caravana do tipo " << tipo << " foi destruída!" << std::endl;
        mapa->atualizarPosicao(linha, coluna, '.');
    }

    if (outra->estaDestruida()) {
        std::cout << "A caravana do tipo " << outra->getTipo() << " foi destruída!" << std::endl;
        mapa->atualizarPosicao(outra->getLinha(), outra->getColuna(), '.');
    }
}

int Caravana::getLinha() const {
    return linha;
}

int Caravana::getColuna() const {
    return coluna;
}

std::string Caravana::getTipo() const {
    return tipo;
}

void Caravana::adicionarTripulantes(int quantidade) {
    tripulacao += quantidade;
    if (tripulacao > capacidadeCarga) {
        tripulacao = capacidadeCarga;
    }
}

void Caravana::removerTripulantes(int quantidade) {
    tripulacao -= quantidade;
    if (tripulacao < 0) {
        tripulacao = 0;
    }
}

void Caravana::adicionarMoedas(int quantidade) {
    moedas += quantidade;
}

int Caravana::getTripulacao() const {
    return tripulacao;
}

int Caravana::getMoedas() const {
    return moedas;
}
