// Item.cpp
#include "Item.h"

Item::Item(int linha, int coluna, const std::string& tipo, int duracao)
        : linha(linha), coluna(coluna), tipo(tipo), duracao(duracao) {}

int Item::getLinha() const {
    return linha;
}

int Item::getColuna() const {
    return coluna;
}

std::string Item::getTipo() const {
    return tipo;
}

int Item::getDuracao() const {
    return duracao;
}

void Item::reduzirDuracao() {
    if (duracao > 0) {
        --duracao;
    }
}
