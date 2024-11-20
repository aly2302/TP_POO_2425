// Caravana.cpp
#include "Caravana.h"
#include <iostream>

Caravana::Caravana(int linha, int coluna, int capacidadeCarga, int tripulacao, int agua, const std::string& tipo)
        : linha(linha), coluna(coluna), capacidadeCarga(capacidadeCarga), tripulacao(tripulacao), agua(agua), tipo(tipo), movimentoAutomatico(false) {}

void Caravana::mover(int novaLinha, int novaColuna) {
    linha = novaLinha;
    coluna = novaColuna;
}

void Caravana::imprimirInfo() const {
    std::cout << "Caravana do tipo " << tipo << " na posição (" << linha << ", " << coluna << ")" << std::endl;
}

void Caravana::executarMovimentoAutonomo() {
    // Implementação fictícia para movimentação automática
    linha += 1;
    coluna += 1;
}

void Caravana::ativarMovimentoAutomatico() {
    movimentoAutomatico = true;
}

void Caravana::desativarMovimentoAutomatico() {
    movimentoAutomatico = false;
}

bool Caravana::getMovimentoAutomatico() const {
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

void Caravana::adicionarAgua(int quantidade) {
    agua += quantidade;
}

void Caravana::adicionarTripulacao(int quantidade) {
    tripulacao += quantidade;
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

// Implementação das subclasses
CaravanaComercio::CaravanaComercio(int linha, int coluna)
        : Caravana(linha, coluna, 100, 10, 50, "Comércio") {}

void CaravanaComercio::executarMovimentoAutonomo() {
    // Implementação específica para movimentação automática da caravana de comércio
    linha += 1;
}

CaravanaMilitar::CaravanaMilitar(int linha, int coluna)
        : Caravana(linha, coluna, 150, 20, 100, "Militar") {}

void CaravanaMilitar::executarMovimentoAutonomo() {
    // Implementação específica para movimentação automática da caravana militar
    linha -= 1;
}

CaravanaSecreta::CaravanaSecreta(int linha, int coluna)
        : Caravana(linha, coluna, 50, 5, 20, "Secreta") {}

void CaravanaSecreta::executarMovimentoAutonomo() {
    // Implementação específica para movimentação automática da caravana secreta
    coluna -= 1;
}

CaravanaBarbara::CaravanaBarbara(int linha, int coluna)
        : Caravana(linha, coluna, 200, 15, 0, "Bárbara") {}

void CaravanaBarbara::executarMovimentoAutonomo() {
    // Implementação específica para movimentação automática da caravana bárbara
    linha -= 1;
    coluna += 1;
}