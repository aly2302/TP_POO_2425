// Item.h
#ifndef TP_POO_2425_ITEM_H
#define TP_POO_2425_ITEM_H

class Item {
public:
    int linha;
    int coluna;
    char simbolo; // Ex: 'I' para identificar itens

    Item(int linha, int coluna, char simbolo) : linha(linha), coluna(coluna), simbolo(simbolo) {}
};

#endif // TP_POO_2425_ITEM_H
