#ifndef TP_POO_2425_ITEM_H
#define TP_POO_2425_ITEM_H

#include <string>

class Caravana; // Declaração antecipada para evitar dependências circulares
class Mapa;     // Declaração antecipada para interagir com o mapa

class Item {
public:
    enum Tipo {
        CaixaPandora,
        ArcaTesouro,
        Jaula,
        Mina,
        Surpresa
    };

    int linha;
    int coluna;
    Tipo tipo;
    int duracao; // Duração em instantes
    char simbolo; // Representação visual (Ex.: 'I')

    // Construtor
    Item(int linha, int coluna, Tipo tipo, int duracao)
            : linha(linha), coluna(coluna), tipo(tipo), duracao(duracao), simbolo('I') {}

    // Aplica o efeito do item em uma caravana
    void aplicarEfeito(Caravana& caravana, Mapa& mapa);

    // Retorna o nome do tipo do item
    std::string getNomeTipo() const;
};

#endif // TP_POO_2425_ITEM_H