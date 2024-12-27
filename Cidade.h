#ifndef TP_POO_2425_CIDADE_H
#define TP_POO_2425_CIDADE_H

#include <iostream>
#include <string>
#include <vector>
#include "Mapa.h"

class Cidade {
private:
    std::string nome;
    int linha;
    int coluna;
    std::vector<std::unique_ptr<Caravana>> caravanasDisponiveis;
    Mapa& mapa; // Referência ao objeto Mapa

    // Método para inicializar caravanas
    void inicializarCaravanas() {
        int id_caravana;
        id_caravana = mapa.gerarIDCaravana();
        caravanasDisponiveis.push_back(std::make_unique<CaravanaComercio>(id_caravana, linha, coluna));

        id_caravana = mapa.gerarIDCaravana();
        caravanasDisponiveis.push_back(std::make_unique<CaravanaMilitar>(id_caravana, linha, coluna));

        id_caravana = mapa.gerarIDCaravana();
        caravanasDisponiveis.push_back(std::make_unique<CaravanaSecreta>(id_caravana, linha, coluna));
    }

public:
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

    // Método para comprar uma caravana
    bool comprarCaravana();

    // Outros métodos
    void imprimirDetalhes() const;
};

#endif // TP_POO_2425_CIDADE_H

