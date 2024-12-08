// Alterações no ficheiro Buffer.cpp
#include "Buffer.h"
#include <cstring>

Buffer::Buffer(int linhas, int colunas) : linhas(linhas), colunas(colunas), cursorLinha(0), cursorColuna(0) {
    buffer = new char[linhas * colunas];
    limparBuffer();
}

Buffer::~Buffer() {
    delete[] buffer;
}

void Buffer::limparBuffer() {
    std::memset(buffer, ' ', linhas * colunas);
}

void Buffer::moverCursor(int linha, int coluna) {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        cursorLinha = linha;
        cursorColuna = coluna;
    } else {
        throw std::out_of_range("Coordenadas do cursor fora do limite do buffer.");
    }
}

void Buffer::escreverCaractere(char c) {
    int index = cursorLinha * colunas + cursorColuna;
    if (index < linhas * colunas) {
        buffer[index] = c;
        cursorColuna = (cursorColuna + 1) % colunas;
    }
}

void Buffer::escreverString(const char* str) {
    while (*str) {
        escreverCaractere(*str++);
    }
}

void Buffer::imprimirBuffer() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            std::cout << buffer[i * colunas + j];
        }
        std::cout << std::endl;
    }
}

Buffer& Buffer::operator<<(const char* str) {
    if (str) {
        while (*str) {
            escreverCaractere(*str++);
        }
    }
    return *this;
}

Buffer& Buffer::operator<<(char c) {
    escreverCaractere(c);
    return *this;
}
