#ifndef TP_POO_2425_CIDADE_H
#define TP_POO_2425_CIDADE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

class Caravana;

class Mapa;

class Cidade {
private:
    std::string nome;
    int linha;
    int coluna;
    std::vector<std::unique_ptr<Caravana>> caravanasDisponiveis;
    Mapa& mapa;  // Add a reference to Mapa

public:
    // Add Mapa reference to the constructor
    Cidade(const std::string& nome, int linha, int coluna, Mapa& mapa)
            : nome(nome), linha(linha), coluna(coluna), mapa(mapa) {
        inicializarCaravanas();
    }

    // Destrutor para liberar memória
    ~Cidade() = default;

    // Métodos de acesso
    const std::string& getNome() const { return nome; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }

    void inicializarCaravanas();

    // Método para comprar uma caravana
    bool comprarCaravana(char tipo);

    // Método para comprar Tripulantes
    void comprarTripulantes(int idCaravana, int quantidade) const;

    // Método para comprar Mercadoria
    void comprarMercadoria(int idCaravana, int quantidade) const;

    // Método para vender Mercadoria
    void venderMercadoria(int idCaravana) const;

    // Outros métodos
    void imprimirDetalhes() const;
    void imprimirPrecos() const;
};

#endif // TP_POO_2425_CIDADE_H
