// Buffer.cpp
#include "Buffer.h"
#include <iostream>

Buffer::Buffer(int linhas, int colunas) : linhas(linhas), colunas(colunas), cursorLinha(0), cursorColuna(0) {
    buffer = new char[linhas * colunas];
    esvaziarBuffer();
}

Buffer::~Buffer() {
    delete[] buffer;
}

void Buffer::esvaziarBuffer() {
    for (int i = 0; i < linhas * colunas; ++i) {
        buffer[i] = ' ';
    }
}

void Buffer::moverCursor(int linha, int coluna) {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        cursorLinha = linha;
        cursorColuna = coluna;
    }
}

void Buffer::imprimirChar(char c) {
    if (cursorLinha >= 0 && cursorLinha < linhas && cursorColuna >= 0 && cursorColuna < colunas) {
        buffer[cursorLinha * colunas + cursorColuna] = c;
        cursorColuna++;
        if (cursorColuna >= colunas) {
            cursorColuna = 0;
            cursorLinha++;
        }
    }
}

void Buffer::imprimirString(const std::string& str) {
    for (char c : str) {
        imprimirChar(c);
    }
}

void Buffer::imprimirInt(int valor) {
    imprimirString(std::to_string(valor));
}

void Buffer::transcreverParaConsola() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            std::cout << buffer[i * colunas + j];
        }
        std::cout << '\n';
    }
}