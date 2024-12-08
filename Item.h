#ifndef TP_POO_2425_ITEM_H
#define TP_POO_2425_ITEM_H

class Item {
public:
    int linha;
    int coluna;
    char simbolo; // Ex: 'I' para identificar itens
    int duracao;  // Duração em turnos

    Item(int linha, int coluna, char simbolo, int duracao)
            : linha(linha), coluna(coluna), simbolo(simbolo), duracao(duracao) {}
};

#endif // TP_POO_2425_ITEM_H
