#ifndef TP_POO_2425_CARAVANA_H
#define TP_POO_2425_CARAVANA_H

#include <string>

class Caravana {
protected:
    int linha;
    int coluna;
    int capacidadeCarga;
    int tripulacao;
    int agua;
    std::string tipo;
    bool movimentoAutomatico;

public:
    // Construtor
    Caravana(int linha, int coluna, int capacidadeCarga, int tripulacao, int agua, const std::string& tipo);

    // Métodos comuns
    virtual void mover(int novaLinha, int novaColuna);
    virtual void imprimirInfo() const;
    virtual void executarMovimentoAutonomo();

    // Métodos para ativar/desativar movimento automático
    void ativarMovimentoAutomatico();
    void desativarMovimentoAutomatico();

    // Método getter para movimento automático
    bool getMovimentoAutomatico() const;

    // Métodos para combate
    void sofrerDano(int dano);
    bool estaDestruida() const;

    // Métodos para interação com itens
    void adicionarAgua(int quantidade);
    void adicionarTripulacao(int quantidade);

    // Obter posição
    int getLinha() const;
    int getColuna() const;
    std::string getTipo() const;
};

// Subclasses específicas
class CaravanaComercio : public Caravana {
public:
    CaravanaComercio(int linha, int coluna);
    void executarMovimentoAutonomo() override;
};

class CaravanaMilitar : public Caravana {
public:
    CaravanaMilitar(int linha, int coluna);
    void executarMovimentoAutonomo() override;
};

class CaravanaSecreta : public Caravana {
public:
    CaravanaSecreta(int linha, int coluna);
    void executarMovimentoAutonomo() override;
};

class CaravanaBarbara : public Caravana {
public:
    CaravanaBarbara(int linha, int coluna);
    void executarMovimentoAutonomo() override;
};


#endif //TP_POO_2425_CARAVANA_H
