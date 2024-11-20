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
    // Construtor para inicializar um item com linha, coluna, tipo e duração
    Item(int linha, int coluna, const std::string& tipo, int duracao);

    // Métodos para obter informações do item
    int getLinha() const;
    int getColuna() const;
    std::string getTipo() const;
    int getDuracao() const;

    // Método para reduzir a duração do item
    void reduzirDuracao();

    // Método para verificar se o item ainda está ativo
    bool estaAtivo() const;
};


#endif //TP_POO_2425_ITEM_H
