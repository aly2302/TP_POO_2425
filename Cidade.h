#ifndef TP_POO_2425_CIDADE_H
#define TP_POO_2425_CIDADE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include "Mapa.h"      // Certifique-se de que Mapa.h está incluído
#include "Caravana.h"  // Inclua Caravana.h para que Caravana e suas subclasses sejam conhecidas

class Cidade {
private:
    std::string nome;
    int linha;
    int coluna;
    int preco_compra = 1;
    int preco_venda = 2;
    std::vector<std::unique_ptr<Caravana>> caravanasDisponiveis;
    Mapa& mapa; // Referência ao objeto Mapa

    // Método para inicializar caravanas
    void inicializarCaravanas() {
        int id_caravana;

        // Inicializa Caravana de Comércio
        id_caravana = mapa.gerarIDCaravana();
        caravanasDisponiveis.push_back(std::unique_ptr<Caravana>(new CaravanaComercio(id_caravana, linha, coluna)));

        // Inicializa Caravana Militar
        id_caravana = mapa.gerarIDCaravana();
        caravanasDisponiveis.push_back(std::unique_ptr<Caravana>(new CaravanaMilitar(id_caravana, linha, coluna)));

        // Inicializa Caravana Secreta
        id_caravana = mapa.gerarIDCaravana();
        caravanasDisponiveis.push_back(std::unique_ptr<Caravana>(new CaravanaSecreta(id_caravana, linha, coluna)));
    }

public:
    Cidade(const std::string& nome, int linha, int coluna, int preco_compra, int preco_venda, Mapa& mapa)
            : nome(nome), linha(linha), coluna(coluna), preco_compra(preco_compra), preco_venda(preco_venda), mapa(mapa) {
        inicializarCaravanas();
    }

    // Destrutor para liberar memória
    ~Cidade() = default;

    // Métodos de acesso
    const std::string& getNome() const { return nome; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }

    int getPreco_Compra() const { return preco_compra; }
    int getPreco_Venda() const { return preco_venda; }

    // Método para comprar uma caravana
    bool comprarCaravana(char tipo);

    // Método para comprar Tripulantes
    void comprarTripulantes(int idCaravana, int quantidade) const;

    // Método para comprar Mercadoria
    void comprarMercadoria(int idCaravana, int quantidade, int preco_compra = 1) const;

    // Método para vender Mercadoria
    void venderMercadoria(int idCaravana, int preco_venda = 1) const;

    // Outros métodos
    void imprimirDetalhes() const;
    void imprimirPrecos() const;
};

#endif // TP_POO_2425_CIDADE_H
