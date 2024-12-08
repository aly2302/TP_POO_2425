#ifndef TP_POO_2425_BUFFER_H
#define TP_POO_2425_BUFFER_H

#include <iostream>

class Buffer {
private:
    int linhas;
    int colunas;
    char* buffer;
    int cursorLinha;
    int cursorColuna;

public:
    Buffer(int linhas, int colunas);
    ~Buffer();
    void limparBuffer();
    void moverCursor(int linha, int coluna);
    void escreverCaractere(char c);
    void escreverString(const char* str);
    void imprimirBuffer() const;

    // Operadores sobrecarregados
    Buffer& operator<<(const char* str);
    Buffer& operator<<(char c);
};

#endif //TP_POO_2425_BUFFER_H