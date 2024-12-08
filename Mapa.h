#ifndef TP_POO_2425_MAPA_H
#define TP_POO_2425_MAPA_H

#include <vector>
#include <memory>
#include <string>
#include "Caravana.h"
#include "Item.h"
#include "Cidade.h"
#include "Buffer.h"

class Mapa {
private:
    // Atributos do mapa
    int linhas;
    int colunas;
    char* grid;
    Buffer* buffer; // Ponteiro para o buffer para exibição

    // Parâmetros configuráveis
    int moedas;
    int instantesEntreNovosItens;
    int duracaoItem;
    int maxItens;
    int precoVendaMercadoria;
    int precoCompraMercadoria;
    int precoCaravana;
    int instantesEntreNovosBarbaros;
    int duracaoBarbaros;

    // Listas de entidades
    std::vector<std::unique_ptr<Caravana>> caravanas;
    std::vector<Item> itens;
    std::vector<Cidade> cidades;

    // Métodos auxiliares
    int calcularIndice(int linha, int coluna) const;
    bool posicaoValida(int linha, int coluna) const;

public:
    // Construtor e destrutor
    Mapa(const std::string& nomeFicheiro, Buffer* buffer);
    ~Mapa();

    // Métodos de acesso a parâmetros configuráveis
    int getMoedas() const;
    int getInstantesEntreNovosItens() const;
    int getDuracaoItem() const;
    int getMaxItens() const;
    int getPrecoVendaMercadoria() const;
    int getPrecoCompraMercadoria() const;
    int getPrecoCaravana() const;
    int getInstantesEntreNovosBarbaros() const;
    int getDuracaoBarbaros() const;
    int getNumeroCaravanas() const;
    bool reduzirMoedas(int quantidade);


    // Gerenciamento do grid
    void atualizarGrid(int linha, int coluna, char simbolo);
    char obterGrid(int linha, int coluna) const;
    void imprimirMapa() const;

    // Gerenciamento de caravanas
    void adicionarCaravana(std::unique_ptr<Caravana> caravana);
    void moverCaravana(int id, int novaLinha, int novaColuna);
    std::vector<std::pair<int, int>> encontrarCaravanasAdjacentes(int linha, int coluna) const;
    Caravana* encontrarCaravanaBarbaraProxima(int linha, int coluna, int raio) const;

    // Gerenciamento de itens
    void adicionarItem(const Item& item);
    Item* encontrarItemProximo(int linha, int coluna, int raio) const;

    // Gerenciamento de cidades
    void adicionarCidade(const Cidade& cidade);
    void listarCidades() const;

    // Lógica de simulação
    void executarSimulacao();
    bool resolverCombates(int& combatesVencidos);

    // Métodos auxiliares
    bool estaAdjacente(int linha1, int coluna1, int linha2, int coluna2) const;
    bool simularCombate(Caravana& jogador, Caravana& barbara);
    std::pair<int, int> gerarMovimentoAleatorio(int linha, int coluna) const;
};

#endif // TP_POO_2425_MAPA_H
