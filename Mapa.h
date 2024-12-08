#ifndef TP_POO_2425_MAPA_H
#define TP_POO_2425_MAPA_H

#include <vector>
#include <memory>
#include <string>
#include "Caravana.h"
#include "Item.h"
#include "Cidade.h"

class Mapa {
private:
    int linhas;
    int colunas;
    char* grid;

    // Parâmetros adicionais
    int moedas;
    int instantesEntreNovosItens;
    int duracaoItem;
    int maxItens;
    int precoVendaMercadoria;
    int precoCompraMercadoria;
    int precoCaravana;
    int instantesEntreNovosBarbaros;
    int duracaoBarbaros;

    std::vector<std::unique_ptr<Caravana>> caravanas;
    std::vector<Item> itens;
    std::vector<Cidade> cidades;

    int calcularIndice(int linha, int coluna) const;
    bool posicaoValida(int linha, int coluna) const;

public:
    // Construtor
    Mapa(const std::string& nomeFicheiro);
    ~Mapa();

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

    void adicionarCidade(const Cidade& cidade);
    void listarCidades() const;


    void executarSimulacao();

    // Outros
    std::pair<int, int> gerarMovimentoAleatorio(int linha, int coluna) const;
};

#endif // TP_POO_2425_MAPA_H