#ifndef TP_POO_2425_CIDADE_H
#define TP_POO_2425_CIDADE_H

#include <iostream>
#include <string>

class Cidade {
private:
    std::string nome;
    int linha;
    int coluna;

public:
    Cidade(const std::string& nome, int linha, int coluna) : nome(nome), linha(linha), coluna(coluna) {}

    // Métodos de acesso
    const std::string& getNome() const { return nome; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }

    // Outros métodos
    void imprimirDetalhes() const {
        std::cout << "Cidade: " << nome << " em (" << linha << ", " << coluna << ")" << std::endl;
    }
};

#endif // TP_POO_2425_CIDADE_H

