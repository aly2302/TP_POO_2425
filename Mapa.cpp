// Mapa.cpp
#include "Mapa.h"
#include <iostream>
#include <fstream>

Mapa::Mapa(const std::string& nomeFicheiro) {
    std::ifstream file(nomeFicheiro);
    if (file.is_open()) {
        file >> linhas >> colunas;
        grid.resize(linhas * colunas, '.');
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                file >> grid[calcularIndice(i, j)];
            }
        }
        file.close();
    } else {
        throw std::runtime_error("Erro ao abrir o ficheiro do mapa");
    }
}

void Mapa::atualizarPosicao(int linha, int coluna, char simbolo) {
    grid[calcularIndice(linha, coluna)] = simbolo;
}

char Mapa::obterPosicao(int linha, int coluna) const {
    return grid[calcularIndice(linha, coluna)];
}

int Mapa::getLinhas() const {
    return linhas;
}

int Mapa::getColunas() const {
    return colunas;
}

int Mapa::calcularIndice(int linha, int coluna) const {
    return linha * colunas + coluna;
}

void Mapa::imprimirMapa(Buffer& buffer) const {
    buffer.limparBuffer();
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            buffer.moverCursor(i, j);
            buffer.escreverCaractere(grid[calcularIndice(i, j)]);
        }
    }
    buffer.imprimirBuffer();
}
