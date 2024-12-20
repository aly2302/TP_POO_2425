// Buffer.h - Revisado e otimizado
#ifndef TP_POO_2425_BUFFER_H
#define TP_POO_2425_BUFFER_H

#include <iostream>
#include <cstddef>

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
    void escreverInteiro(int num);
    void imprimirBuffer() const;

    Buffer& operator<<(const char* str);
    Buffer& operator<<(char c);
    Buffer& operator<<(int num);
    Buffer& operator<<(std::size_t num); // Adicionado para resolver ambiguidade
};

#endif // TP_POO_2425_BUFFER_H
