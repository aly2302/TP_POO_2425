// Buffer.cpp - Revisado e otimizado
#include "Buffer.h"
#include <cstring>

Buffer::Buffer(int linhas, int colunas)
        : linhas(linhas), colunas(colunas), cursorLinha(0), cursorColuna(0) {
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
        if (cursorColuna == 0) {
            cursorLinha = (cursorLinha + 1) % linhas;
        }
    }
}

void Buffer::escreverString(const char* str) {
    while (*str) {
        escreverCaractere(*str++);
    }
}

void Buffer::escreverInteiro(int num) {
    char numStr[12]; // Buffer suficiente para números inteiros
    std::snprintf(numStr, sizeof(numStr), "%d", num);
    escreverString(numStr);
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
        escreverString(str);
    }
    return *this;
}

Buffer& Buffer::operator<<(char c) {
    escreverCaractere(c);
    return *this;
}

Buffer& Buffer::operator<<(int num) {
    escreverInteiro(num);
    return *this;
}

Buffer& Buffer::operator<<(std::size_t num) {
    escreverInteiro(static_cast<int>(num)); // Converte para int (assumindo que o valor é pequeno)
    return *this;
}
