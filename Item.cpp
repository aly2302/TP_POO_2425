#include "Item.h"
#include "Caravana.h"
#include "Mapa.h"
#include <iostream>

// Aplica o efeito do item na caravana
void Item::aplicarEfeito(Caravana& caravana, Mapa& mapa) {
    switch (tipo) {
        case CaixaPandora:
            std::cout << "Caravana " << caravana.getId() << " apanhou uma Caixa de Pandora.\n";
            caravana.removerTripulantes(static_cast<int>(caravana.getTripulantes() * 0.20));
            break;
        case ArcaTesouro:
            std::cout << "Caravana " << caravana.getId() << " apanhou uma Arca do Tesouro.\n";
            mapa.addMoedas(static_cast<int>(mapa.getMoedas() * 0.10));
            break;
        case Jaula:
            std::cout << "Caravana " << caravana.getId() << " apanhou uma Jaula.\n";
            caravana.adicionarTripulantes(10); // Exemplo: Adiciona até 10 tripulantes
            break;
        case Mina:
            std::cout << "Caravana " << caravana.getId() << " apanhou uma Mina.\n";
            mapa.removerCaravana(caravana.getId()); // Remove a caravana do mapa
            break;
        case Surpresa:
            std::cout << "Caravana " << caravana.getId() << " apanhou uma Surpresa. Efeito aleatório!\n";
            if (rand() % 2 == 0) {
                caravana.adicionarTripulantes(5); // Exemplo: Surpresa boa
            } else {
                caravana.removerTripulantes(5); // Exemplo: Surpresa ruim
            }
            break;
    }
}

// Retorna o nome do tipo do item
std::string Item::getNomeTipo() const {
    switch (tipo) {
        case CaixaPandora: return "Caixa de Pandora";
        case ArcaTesouro:  return "Arca do Tesouro";
        case Jaula:        return "Jaula";
        case Mina:         return "Mina";
        case Surpresa:     return "Surpresa";
        default:           return "Desconhecido";
    }
}