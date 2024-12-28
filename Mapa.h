<<<<<<< HEAD
<<<<<<< HEAD
#ifndef TP_POO_2425_MAPA_H
#define TP_POO_2425_MAPA_H

#include "Cidade.h"  // or the correct path to Cidade.h
=======
#ifndef TP_POO_2425_MAPA_H
#define TP_POO_2425_MAPA_H

>>>>>>> bf799d04c67bee4d648f8bdc8292e8d955a71b73
#include <vector>
#include <memory>
#include <string>
#include "Caravana.h"
#include "Item.h"
#include "Buffer.h"

<<<<<<< HEAD

=======
>>>>>>> bf799d04c67bee4d648f8bdc8292e8d955a71b73
class Mapa {
private:
    int linhas;
    int colunas;
    char* grid;
<<<<<<< HEAD
    Buffer* buffer; // Ponteiro para o buffer associado

    // Parâmetros adicionais
=======
    Buffer* buffer;

>>>>>>> bf799d04c67bee4d648f8bdc8292e8d955a71b73
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
<<<<<<< HEAD
    std::vector<Cidade*> cidades; // Usar ponteiros para evitar cópias desnecessárias
=======
>>>>>>> bf799d04c67bee4d648f8bdc8292e8d955a71b73

    int calcularIndice(int linha, int coluna) const;
    bool posicaoValida(int linha, int coluna) const;

public:
<<<<<<< HEAD
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
    void adicionarCidade(Cidade* cidade); // Passar um ponteiro para a cidade
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

=======

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





>>>>>>> edaf6dfd9e943aae394fe67968b52d284cce5047
#endif // TP_POO_2425_MAPA_H
=======
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
    bool addMoedas(int quantidade);
    int gerarIDCaravana();

    void executarSimulacao();
    void imprimirMapa() const;
    void atualizarBuffer();

    // Verificar se duas posições no mapa são adjacentes
    bool estaAdjacente(int linha1, int coluna1, int linha2, int coluna2) const;

// Encontrar caravanas adjacentes a uma posição no mapa
    std::vector<std::pair<int, int>> encontrarCaravanasAdjacentes(int linha, int coluna) const;

    const std::vector<std::unique_ptr<Caravana>>& getCaravanas() const;


};

#endif // TP_POO_2425_MAPA_H
>>>>>>> bf799d04c67bee4d648f8bdc8292e8d955a71b73
