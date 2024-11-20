#ifndef TP_POO_2425_MAPA_H
#define TP_POO_2425_MAPA_H

#include <vector>
#include <string>

class Mapa {
private:
    std::vector<std::vector<char>> grelha;
    int linhas;
    int colunas;

public:
    // Construtor para inicializar o mapa a partir de um ficheiro
    Mapa(const std::string& nomeFicheiro);

    // Método para imprimir o mapa na consola
    void imprimirMapa() const;

    // Método para obter o tipo de zona numa posição específica
    char obterZona(int linha, int coluna) const;

    // Método para atualizar uma posição no mapa
    void atualizarPosicao(int linha, int coluna, char valor);

    // Métodos para obter dimensões do mapa
    int getLinhas() const;
    int getColunas() const;
};

#endif // TP_POO_2425_MAPA_H
