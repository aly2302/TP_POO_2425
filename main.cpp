#include <iostream>
#include "Mapa.h"

int main() {
    try {
        // Criando um arquivo de exemplo para o mapa
        std::string mapFile = "config.txt";

        // Criar e inicializar o mapa a partir de um arquivo
        Mapa mapa(mapFile);

        // Mostrar o mapa no console (estado inicial)
        std::cout << "Mapa inicial:" << std::endl;
        mapa.mostrarMapa();

        // Teste de movimentação de caravanas (ou outros itens) no mapa
        std::cout << "\nMovendo um item (A) para a posição (2, 3):" << std::endl;
        mapa.moverCaravana('A', 2, 3);  // Mover um item "A" para a posição (2, 3)
        mapa.mostrarMapa();

        // Outro movimento para testar a mudança no mapa
        std::cout << "\nMovendo um item (B) para a posição (1, 5):" << std::endl;
        mapa.moverCaravana('B', 1, 5);  // Mover um item "B" para a posição (1, 5)
        mapa.mostrarMapa();

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}

