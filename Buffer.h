#ifndef TP_POO_2425_BUFFER_H
#define TP_POO_2425_BUFFER_H

#include <iostream>
#include <stdexcept>
#include <string>

class Buffer {
    char* grid;              // Armazena o buffer como um array linear
    int rows, cols;          // Dimensões do buffer
    int cursor_row, cursor_col; // Posição atual do cursor

public:
    // Construtor que inicializa o buffer com as dimensões especificadas
    Buffer(int rows, int cols);

    // Destrutor para liberar memória
    ~Buffer();

    // Esvaziar o buffer (preencher com espaços)
    void clear();

    // Transcrever o conteúdo do buffer para a consola
    void print() const;

    // Mover o cursor para uma posição específica
    void moveCursor(int row, int col);

    // Escrever um caráter no buffer
    void write(char c);

    // Escrever uma string no buffer
    void write(const char* str);

    // Escrever um inteiro no buffer
    void write(int num);

    // Operadores para facilitar uso
    Buffer& operator<<(char c);
    Buffer& operator<<(const char* str);
    Buffer& operator<<(int num);

private:
    // Avança o cursor para a próxima posição
    void advanceCursor();
};


#endif //TP_POO_2425_BUFFER_H
