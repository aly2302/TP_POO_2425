#ifndef TP_POO_2425_CARAVANA_H
#define TP_POO_2425_CARAVANA_H

#include <string>
#include <iostream>
#include <memory>
#include "Item.h"
#include "Buffer.h"

class Mapa;

// Classe base abstrata para caravanas
class Caravana {
protected:
    int id;
    int linha;
    int coluna;
    int capacidadeCarga;
    int capacidadeAgua;
    int tripulantes;
    int aguaAtual;
    int cargaAtual;

public:
    Caravana(int id, int linha, int coluna, int capacidadeCarga, int capacidadeAgua, int tripulantesInicial);
    virtual ~Caravana() = default;

    // Métodos de acesso
    int getId() const;
    int getLinha() const;
    int getColuna() const;
    int getCapacidadeCarga() const;
    int getCapacidadeAgua() const;
    int getTripulantes() const;
    int getAguaAtual() const;
    int getCargaAtual() const;
    virtual std::string getTipo() const = 0;

    // Métodos modificadores
    void moverPara(int novaLinha, int novaColuna);
    void adicionarCarga(int quantidade);
    void removerCarga(int quantidade);
    void consumirAgua(int quantidade);
    void adicionarTripulantes(int quantidade);
    void removerTripulantes(int quantidade);

    // Comportamentos polimórficos
    virtual bool estaSemAgua() const = 0;
    virtual bool estaCheia() const = 0;
    virtual void executarComportamento(Mapa& mapa) = 0;
};

// Caravana de Comércio
class CaravanaComercio : public Caravana {
public:
    CaravanaComercio(int id, int linha, int coluna);
    bool estaSemAgua() const override;
    bool estaCheia() const override;
    void executarComportamento(Mapa& mapa) override;

    std::string getTipo() const override { return "Comercio"; }
};

// Caravana Militar
class CaravanaMilitar : public Caravana {
public:
    CaravanaMilitar(int id, int linha, int coluna);
    bool estaSemAgua() const override;
    bool estaCheia() const override;
    void executarComportamento(Mapa& mapa) override;
    std::string getTipo() const override { return "Militar"; }
};

// Caravana Secreta
class CaravanaSecreta : public Caravana {
public:
    CaravanaSecreta(int id, int linha, int coluna);
    bool estaSemAgua() const override;
    bool estaCheia() const override;
    void executarComportamento(Mapa& mapa) override;
    std::string getTipo() const override { return "Secreta"; }
};

// Caravana Bárbara
class CaravanaBarbara : public Caravana {
public:
    CaravanaBarbara(int id, int linha, int coluna);
    bool estaSemAgua() const override { return false; } // Bárbaros não consomem água
    bool estaCheia() const override { return false; }   // Bárbaros não têm capacidade de carga
    void executarComportamento(Mapa& mapa) override;
    std::string getTipo() const override { return "Barbara"; }
};

#endif // TP_POO_2425_CARAVANA_H