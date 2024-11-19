#ifndef TP_POO_2425_MAPA_H
#define TP_POO_2425_MAPA_H

#include "Buffer.h"
#include <string>
#include <stdexcept>

class Mapa {
    int rows, cols;          // Dimensões do mapa
    Buffer* buffer;          // Ponteiro para o buffer (simula o ecrã)
    char** grid;             // Estrutura lógica do mapa (estado interno)

public:
    Mapa(const std::string& fileName);
    ~Mapa();

    void carregarMapa(const std::string& fileName);
    void atualizarBuffer();
    void mostrarMapa() const;
    void moverCaravana(char id, int novaLinha, int novaColuna);
};

#endif // TP_POO_2425_MAPA_H
