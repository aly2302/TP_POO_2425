#ifndef TP_POO_2425_COMANDOS_H
#define TP_POO_2425_COMANDOS_H

#include "Mapa.h"
#include "Caravana.h"
#include "Item.h"
#include <string>
#include <vector>

class Comandos {
private:
    Mapa* mapa;
    std::vector<Caravana*> caravanas;
    std::vector<Item*> itens;
    int turnosParaTempestade;
    int turnosParaItens;
    int turnosParaBarbaros;

public:
    // Construtor
    Comandos(Mapa* mapa);

    // Método para interpretar comandos do utilizador
    void interpretarComando(const std::string& comando);

    // Método para adicionar caravanas e itens
    void adicionarCaravana(Caravana* caravana);
    void adicionarItem(Item* item);

    // Método para processar turnos
    void processarTurno();

    // Método para gerar tempestade de areia
    void gerarTempestadeDeAreia(int linha, int coluna, int raio);

    // Método para verificar e processar combates
    void verificarCombates();

    // Métodos para interação com cidades
    void venderMercadorias(int idCaravana);
    void comprarTripulantes(int idCaravana, int quantidade);
    void reabastecerAgua(int idCaravana, int quantidade);

    // Métodos para gestão de estados e configuração
    void carregarConfiguracaoInicial(const std::string& ficheiroConfiguracao);
    void salvarEstadoBuffer(const std::string& ficheiroEstado);
    void carregarEstadoBuffer(const std::string& ficheiroEstado);

    int getNumeroCaravanas() const;
    Caravana* getCaravana(int id);


};

#endif //TP_POO_2425_COMANDOS_H
