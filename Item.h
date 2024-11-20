// Item.h
#ifndef TP_POO_2425_ITEM_H
#define TP_POO_2425_ITEM_H

#include <string>

class Item {
private:
    int linha;
    int coluna;
    std::string tipo;
    int duracao;

public:
    Item(int linha, int coluna, const std::string& tipo, int duracao);
    int getLinha() const;
    int getColuna() const;
    std::string getTipo() const;
    int getDuracao() const;
    void reduzirDuracao();
};

#endif //TP_POO_2425_ITEM_H
