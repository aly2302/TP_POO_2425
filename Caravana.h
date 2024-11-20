// Caravana.h
#ifndef TP_POO_2425_CARAVANA_H
#define TP_POO_2425_CARAVANA_H

#include <string>
#include "Mapa.h"

class Caravana {
protected:
    int linha;
    int coluna;
    int capacidadeCarga;
    int tripulacao;
    int agua;
    int moedas;
    std::string tipo;
    bool movimentoAutomatico;

public:
    Caravana(int linha, int coluna, int capacidadeCarga, int tripulacao, int agua, const std::string& tipo);
    void mover(const std::string& direcao, Mapa* mapa);
    void moverNoMapa(Mapa* mapa, int novaLinha, int novaColuna);
    void imprimirInfo() const;
    void executarMovimentoAutonomo(Mapa* mapa);
    void ativarMovimentoAutomatico();
    void desativarMovimentoAutomatico();
    bool isMovimentoAutomatico() const;
    void sofrerDano(int dano);
    bool estaDestruida() const;
    bool estaAdjacente(Caravana* outra) const;
    void combater(Caravana* outra, Mapa* mapa);
    int getLinha() const;
    int getColuna() const;
    std::string getTipo() const;

    void adicionarTripulantes(int quantidade);
    void removerTripulantes(int quantidade);
    void adicionarMoedas(int quantidade);
    int getTripulacao() const;
    int getMoedas() const;
};

#endif //TP_POO_2425_CARAVANA_H
