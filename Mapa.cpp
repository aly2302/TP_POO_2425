// Mapa.cpp
#include "Mapa.h"
#include <fstream>
#include <iostream>

Mapa::Mapa(const std::string& nomeFicheiro) {
    std::ifstream ficheiro(nomeFicheiro);
    if (ficheiro.is_open()) {
        ficheiro >> linhas >> colunas;
        grelha.resize(linhas, std::vector<char>(colunas, '.'));

        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                ficheiro >> grelha[i][j];
            }
        }
        ficheiro.close();
    } else {
        std::cerr << "Erro ao abrir o ficheiro " << nomeFicheiro << std::endl;
    }
}

void Mapa::imprimirMapa() const {
    for (const auto& linha : grelha) {
        for (char zona : linha) {
            std::cout << zona;
        }
        std::cout << '\n';
    }
}

char Mapa::obterZona(int linha, int coluna) const {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        return grelha[linha][coluna];
    }
    return ' '; // Retorna espaço se a posição for inválida
}

void Mapa::atualizarPosicao(int linha, int coluna, char valor) {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        grelha[linha][coluna] = valor;
    }
}

int Mapa::getLinhas() const {
    return linhas;
}

int Mapa::getColunas() const {
    return colunas;
}
