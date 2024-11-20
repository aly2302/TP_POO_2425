// Mapa.h
#ifndef TP_POO_2425_MAPA_H
#define TP_POO_2425_MAPA_H

#include <vector>
#include <string>
#include "Buffer.h"

class Mapa {
private:
    int linhas;
    int colunas;
    std::vector<char> grid;

    int calcularIndice(int linha, int coluna) const;

public:
    Mapa(const std::string& nomeFicheiro);
    void atualizarPosicao(int linha, int coluna, char simbolo);
    char obterPosicao(int linha, int coluna) const;
    int getLinhas() const;
    int getColunas() const;
    void imprimirMapa(Buffer& buffer) const;
};

#endif // TP_POO_2425_MAPA_H
