#include "Comandos.h"
#include "Mapa.h"
#include "Caravana.h"
#include "Item.h"
#include <iostream>

int main() {
    try {
        // Carregar o mapa a partir de um ficheiro
        Mapa mapa("config.txt");

        // Criar o controlador de comandos
        Comandos comandos(&mapa);

        // Adicionar caravanas iniciais ao mapa
        Caravana* caravana1 = new Caravana(1, 1, 100, 10, 50, "Mercante");
        comandos.adicionarCaravana(caravana1);

        Caravana* caravana2 = new Caravana(3, 3, 100, 15, 60, "Exploradora");
        comandos.adicionarCaravana(caravana2);

        // Imprimir o mapa inicial
        Buffer buffer(mapa.getLinhas(), mapa.getColunas());
        mapa.imprimirMapa(buffer);

        // Ciclo principal da simulação
        std::string comando;
        while (true) {
            std::cout << "Digite um comando: ";
            std::getline(std::cin, comando);
            comandos.interpretarComando(comando);
            // Imprimir o mapa após cada comando
            mapa.imprimirMapa(buffer);
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
