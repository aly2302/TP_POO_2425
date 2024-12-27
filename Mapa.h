#ifndef TP_POO_2425_MAPA_H
#define TP_POO_2425_MAPA_H

#include <vector>
#include <memory>
#include <string>
#include "Caravana.h" // Incluído porque o Mapa gerencia Caravanas
#include "Item.h"
#include "Buffer.h"

class Mapa {
private:
    int linhas;
    int colunas;
    char* grid;
    Buffer* buffer;

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

    int calcularIndice(int linha, int coluna) const;
    bool posicaoValida(int linha, int coluna) const;

public:
    Mapa(const std::string& nomeFicheiro, Buffer* buffer);
    ~Mapa();

    int getMoedas() const;
    int getPrecoCaravana() const;
    int getNumeroCaravanas() const;

    void atualizarGrid(int linha, int coluna, char simbolo);
    char obterGrid(int linha, int coluna) const;

    void adicionarCaravana(std::unique_ptr<Caravana> caravana);
    void moverCaravana(int id, int novaLinha, int novaColuna);
    void removerCaravana(int id);
    void adicionarCaravanaBarbaraAleatoria();
    Caravana* encontrarCaravanaBarbaraProxima(int linha, int coluna, int raio) const;

    void adicionarItem(int linha, int coluna);
    void removerItem(int linha, int coluna);
    Item* encontrarItemProximo(int linha, int coluna, int raio) const;

    void contratarTripulantes(int idCaravana, int quantidade);
    void comprarMercadoria(int idCaravana, int quantidade);
    void venderMercadoria(int idCaravana);

    std::pair<int, int> gerarMovimentoAleatorio(int linha, int coluna) const;
    bool reduzirMoedas(int quantidade);
    int gerarIDCaravana();

    void executarSimulacao();
    void imprimirMapa() const;
    void atualizarBuffer();

    // Verificar se duas posições no mapa são adjacentes
    bool estaAdjacente(int linha1, int coluna1, int linha2, int coluna2) const;

// Encontrar caravanas adjacentes a uma posição no mapa
    std::vector<std::pair<int, int>> encontrarCaravanasAdjacentes(int linha, int coluna) const;

};

#endif // TP_POO_2425_MAPA_H
