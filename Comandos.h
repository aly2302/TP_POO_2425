// Comandos.h
#ifndef TP_POO_2425_COMANDOS_H
#define TP_POO_2425_COMANDOS_H

#include <string>
#include <vector>
#include "Mapa.h"
#include "Caravana.h"
#include "Item.h"

class Comandos {
private:
    Mapa* mapa;
    std::vector<Caravana*> caravanas;
    std::vector<Item*> itens;

    int turnosParaTempestade;
    int turnosParaItens;
    int turnosParaBarbaros;

public:
    Comandos(Mapa* mapa);
    void interpretarComando(const std::string& comando);
    void adicionarCaravana(Caravana* caravana);
    void adicionarItem(Item* item);
    void processarTurno();
    void verificarCombates();
    void gerarTempestadeDeAreia(int linha, int coluna, int raio);
    bool validarCaravanaId(int id) const;
    void moverCaravana(const std::string& direcao, int id);
};

#endif // TP_POO_2425_COMANDOS_H
