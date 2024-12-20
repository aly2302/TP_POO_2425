
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
    int linhas;
    int colunas;
    char* grid;
    Buffer* buffer; // Ponteiro para o buffer associado

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
    Mapa(const std::string& nomeFicheiro, Buffer* buffer);
    ~Mapa();

    // Acesso a parâmetros
    int getMoedas() const { return moedas; }
    int getPrecoCaravana() const { return precoCaravana; }
    int getNumeroCaravanas() const;

    // Gerenciamento do grid
    void atualizarGrid(int linha, int coluna, char simbolo);
    char obterGrid(int linha, int coluna) const;

    // Gerenciamento de caravanas
    void adicionarCaravana(std::unique_ptr<Caravana> caravana);
    void moverCaravana(int id, int novaLinha, int novaColuna);
    std::vector<std::pair<int, int>> encontrarCaravanasAdjacentes(int linha, int coluna) const;
    Caravana* encontrarCaravanaBarbaraProxima(int linha, int coluna, int raio) const;

    // Gerenciamento de itens
    void adicionarItem(int linha, int coluna);
    Item* encontrarItemProximo(int linha, int coluna, int raio) const;

    std::pair<int, int> gerarMovimentoAleatorio(int linha, int coluna) const;

    // Gerenciamento de cidades
    void adicionarCidade(const Cidade& cidade);
    void listarCidades() const;

    // Auxiliares
    bool estaAdjacente(int linha1, int coluna1, int linha2, int coluna2) const;
    bool reduzirMoedas(int quantidade);
    int gerarIDCaravana();

    // Simulação
    void executarSimulacao();

    // Imprimir estado do mapa
    void imprimirMapa() const;

    // Mapa.h
    void removerItem(int linha, int coluna);
    void removerCaravana(int id);
    void adicionarCaravanaBarbaraAleatoria();

    void comprarCaravana(const std::string& tipo, const std::string& nomeCidade);
    void venderMercadoria(int idCaravana);
    void comprarMercadoria(int idCaravana, int quantidade);
    void contratarTripulantes(int idCaravana, int quantidade);

    // Atualizar buffer com estado do mapa
    void atualizarBuffer();


};





#endif // TP_POO_2425_MAPA_H