#include "Buffer.h"
#include <iostream>
#include <stdexcept>
#include <string>

// Construtor que inicializa o buffer com as dimensões especificadas
Buffer::Buffer(int rows, int cols)
        : rows(rows), cols(cols), cursor_row(0), cursor_col(0) {
    grid = new char[rows * cols];
    clear();  // Inicializa com espaços
}

// Destrutor para liberar memória
Buffer::~Buffer() {
    delete[] grid;
}

// Esvaziar o buffer (preencher com espaços)
void Buffer::clear() {
    for (int i = 0; i < rows * cols; ++i) {
        grid[i] = ' ';
    }
}

// Transcrever o conteúdo do buffer para a consola
void Buffer::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << grid[i * cols + j];
        }
        std::cout << '\n';
    }
}

// Mover o cursor para uma posição específica
void Buffer::moveCursor(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Cursor fora do limite do buffer");
    }
    cursor_row = row;
    cursor_col = col;
}

// Escrever um caráter no buffer
void Buffer::write(char c) {
    grid[cursor_row * cols + cursor_col] = c;
    advanceCursor();
}

// Escrever uma string no buffer
void Buffer::write(const char* str) {
    while (*str) {
        write(*str++);
    }
}

// Escrever um inteiro no buffer
void Buffer::write(int num) {
    std::string num_str = std::to_string(num);
    for (char c : num_str) {
        write(c);
    }
}

// Operador << para caracteres
Buffer& Buffer::operator<<(char c) {
    write(c);
    return *this;
}

// Operador << para strings
Buffer& Buffer::operator<<(const char* str) {
    write(str);
    return *this;
}

// Operador << para inteiros
Buffer& Buffer::operator<<(int num) {
    write(num);
    return *this;
}

// Avançar o cursor para a próxima posição
void Buffer::advanceCursor() {
    cursor_col++;
    if (cursor_col >= cols) {
        cursor_col = 0;
        cursor_row++;
        if (cursor_row >= rows) {
            cursor_row = 0; // Pode ser ajustado conforme necessidade
        }
    }
}
