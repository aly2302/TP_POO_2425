// Comandos.cpp
#include "Comandos.h"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

Comandos::Comandos(Mapa* mapa) : mapa(mapa), turnosParaTempestade(5), turnosParaItens(10), turnosParaBarbaros(15) {
    std::srand(std::time(nullptr)); // Inicializa o gerador de números aleatórios
}

void Comandos::interpretarComando(const std::string& comando) {
    std::istringstream iss(comando);
    std::string palavra;
    iss >> palavra;

    if (palavra == "config") {
        std::string nomeFicheiro;
        iss >> nomeFicheiro;
        try {
            *mapa = Mapa(nomeFicheiro);
            std::cout << "Mapa configurado a partir do ficheiro: " << nomeFicheiro << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Erro ao configurar o mapa: " << e.what() << std::endl;
        }
    } else if (palavra == "sair") {
        std::cout << "Encerrando o programa..." << std::endl;
        exit(0);
    } else if (palavra == "move") {
        int id;
        std::string direcao;
        iss >> id >> direcao;
        if (validarCaravanaId(id)) {
            moverCaravana(direcao, id);
        } else {
            std::cout << "ID de caravana inválido." << std::endl;
        }
    } else if (palavra == "compra") {
        int id, quantidade;
        iss >> id >> quantidade;
        if (validarCaravanaId(id)) {
            caravanas[id]->adicionarTripulantes(quantidade);
            std::cout << "Comprando " << quantidade << " unidades para a caravana " << id << "." << std::endl;
        } else {
            std::cout << "ID de caravana inválido." << std::endl;
        }
    } else if (palavra == "prox") {
        int turnos;
        iss >> turnos;
        for (int i = 0; i < turnos; ++i) {
            processarTurno();
        }
        std::cout << "Avançando " << turnos << " turnos." << std::endl;
    } else if (palavra == "auto") {
        int id;
        iss >> id;
        if (validarCaravanaId(id)) {
            caravanas[id]->ativarMovimentoAutomatico();
            std::cout << "Movimento automático ativado para a caravana " << id << "." << std::endl;
        } else {
            std::cout << "ID de caravana inválido." << std::endl;
        }
    } else if (palavra == "areia") {
        int linha, coluna, raio;
        iss >> linha >> coluna >> raio;
        gerarTempestadeDeAreia(linha, coluna, raio);
        std::cout << "Tempestade de areia gerada em (" << linha << ", " << coluna << ") com raio " << raio << "." << std::endl;
    } else {
        std::cout << "Comando desconhecido: " << palavra << std::endl;
    }
}

bool Comandos::validarCaravanaId(int id) const {
    return id >= 0 && id < caravanas.size();
}

void Comandos::processarTurno() {
    // Movimentação automática das caravanas
    for (auto& caravana : caravanas) {
        if (caravana->isMovimentoAutomatico()) {
            caravana->executarMovimentoAutonomo(mapa);
        }
    }

    // Gerar novos itens a cada ciclo configurado
    if (--turnosParaItens <= 0) {
        int linha = std::rand() % mapa->getLinhas();
        int coluna = std::rand() % mapa->getColunas();
        if (mapa->obterPosicao(linha, coluna) == '.') {
            Item* novoItem = new Item(linha, coluna, "Surpresa", 20);
            adicionarItem(novoItem);
        }
        turnosParaItens = 10;
    }

    // Movimentação e geração de bárbaros
    if (--turnosParaBarbaros <= 0) {
        int linha = std::rand() % mapa->getLinhas();
        int coluna = std::rand() % mapa->getColunas();
        if (mapa->obterPosicao(linha, coluna) == '.') {
            Caravana* barbaros = new Caravana(linha, coluna, 0, 40, 0, "Bárbara");
            adicionarCaravana(barbaros);
        }
        turnosParaBarbaros = 15;
    }

    verificarCombates();

    // Atualização visual do mapa
    Buffer buffer(mapa->getLinhas(), mapa->getColunas());
    mapa->imprimirMapa(buffer);
}

void Comandos::moverCaravana(const std::string& direcao, int id) {
    int novaLinha = caravanas[id]->getLinha();
    int novaColuna = caravanas[id]->getColuna();

    if (direcao == "D") novaColuna++;
    else if (direcao == "E") novaColuna--;
    else if (direcao == "C") novaLinha--;
    else if (direcao == "B") novaLinha++;
    else if (direcao == "CE") { novaLinha--; novaColuna--; }
    else if (direcao == "CD") { novaLinha--; novaColuna++; }
    else if (direcao == "BE") { novaLinha++; novaColuna--; }
    else if (direcao == "BD") { novaLinha++; novaColuna++; }

    if (mapa->obterPosicao(novaLinha, novaColuna) == '.') {
        caravanas[id]->moverNoMapa(mapa, novaLinha, novaColuna);
        std::cout << "Caravana " << id << " movida para (" << novaLinha << ", " << novaColuna << ")." << std::endl;
    } else {
        std::cout << "Movimento inválido: posição ocupada ou intransponível." << std::endl;
    }
}

void Comandos::verificarCombates() {
    for (size_t i = 0; i < caravanas.size(); ++i) {
        for (size_t j = i + 1; j < caravanas.size(); ++j) {
            Caravana* caravana1 = caravanas[i];
            Caravana* caravana2 = caravanas[j];

            if ((abs(caravana1->getLinha() - caravana2->getLinha()) <= 1) &&
                (abs(caravana1->getColuna() - caravana2->getColuna()) <= 1)) {

                if (caravana1->getTipo() == "Bárbara" || caravana2->getTipo() == "Bárbara") {
                    int dano = std::rand() % 10 + 1;
                    caravana1->sofrerDano(dano);
                    caravana2->sofrerDano(dano);
                    std::cout << "Combate entre " << caravana1->getTipo() << " e " << caravana2->getTipo() << ". Dano infligido: " << dano << std::endl;

                    if (caravana1->estaDestruida()) {
                        std::cout << "A caravana do tipo " << caravana1->getTipo() << " foi destruída!" << std::endl;
                        mapa->atualizarPosicao(caravana1->getLinha(), caravana1->getColuna(), '.');
                        delete caravana1;
                        caravanas.erase(caravanas.begin() + i);
                        --i;
                        break;
                    }

                    if (caravana2->estaDestruida()) {
                        std::cout << "A caravana do tipo " << caravana2->getTipo() << " foi destruída!" << std::endl;
                        mapa->atualizarPosicao(caravana2->getLinha(), caravana2->getColuna(), '.');
                        delete caravana2;
                        caravanas.erase(caravanas.begin() + j);
                        --j;
                    }
                }
            }
        }
    }
}

void Comandos::gerarTempestadeDeAreia(int linha, int coluna, int raio) {
    for (int i = -raio; i <= raio; ++i) {
        for (int j = -raio; j <= raio; ++j) {
            int novaLinha = linha + i;
            int novaColuna = coluna + j;
            if (novaLinha >= 0 && novaLinha < mapa->getLinhas() && novaColuna >= 0 && novaColuna < mapa->getColunas()) {
                mapa->atualizarPosicao(novaLinha, novaColuna, 'A');
            }
        }
    }
}


// Implementação de funções ausentes no Comandos.cpp
void Comandos::adicionarCaravana(Caravana* caravana) {
    caravanas.push_back(caravana);
    mapa->atualizarPosicao(caravana->getLinha(), caravana->getColuna(), 'C');
}

void Comandos::adicionarItem(Item* item) {
    itens.push_back(item);
    mapa->atualizarPosicao(item->getLinha(), item->getColuna(), 'I');
}
