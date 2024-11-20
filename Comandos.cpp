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
        *mapa = Mapa(nomeFicheiro);
        std::cout << "Mapa configurado a partir do ficheiro: " << nomeFicheiro << std::endl;
    } else if (palavra == "sair") {
        std::cout << "Encerrando o programa..." << std::endl;
        exit(0);
    } else if (palavra == "move") {
        int id, linha, coluna;
        iss >> id >> linha >> coluna;
        if (id >= 0 && id < caravanas.size()) {
            caravanas[id]->mover(linha, coluna);
            mapa->atualizarPosicao(linha, coluna, 'C'); // Atualizar posição no mapa
            std::cout << "Caravana " << id << " movida para (" << linha << ", " << coluna << ")." << std::endl;
        } else {
            std::cout << "ID de caravana inválido." << std::endl;
        }
    } else if (palavra == "compra") {
        int id, quantidade;
        iss >> id >> quantidade;
        if (id >= 0 && id < caravanas.size()) {
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
        if (id >= 0 && id < caravanas.size()) {
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

void Comandos::adicionarCaravana(Caravana* caravana) {
    caravanas.push_back(caravana);
}

void Comandos::adicionarItem(Item* item) {
    itens.push_back(item);
    mapa->atualizarPosicao(item->getLinha(), item->getColuna(), 'I');
}

void Comandos::processarTurno() {
    for (auto& caravana : caravanas) {
        if (caravana->getMovimentoAutomatico()) {
            int linhaAtual = caravana->getLinha();
            int colunaAtual = caravana->getColuna();
            mapa->atualizarPosicao(linhaAtual, colunaAtual, '.'); // Limpar posição anterior
            caravana->executarMovimentoAutonomo();
            linhaAtual = caravana->getLinha();
            colunaAtual = caravana->getColuna();
            mapa->atualizarPosicao(linhaAtual, colunaAtual, 'C'); // Atualizar nova posição
        }
    }

    // Processar itens
    for (auto it = itens.begin(); it != itens.end(); ) {
        (*it)->reduzirDuracao();
        if (!(*it)->estaAtivo()) {
            mapa->atualizarPosicao((*it)->getLinha(), (*it)->getColuna(), '.');
            delete *it;
            it = itens.erase(it);
        } else {
            ++it;
        }
    }

    // Geração de tempestades de areia
    if (--turnosParaTempestade <= 0) {
        int linha = std::rand() % mapa->getLinhas();
        int coluna = std::rand() % mapa->getColunas();
        gerarTempestadeDeAreia(linha, coluna, 2);
        turnosParaTempestade = 5;
    }

    // Geração de novos itens
    if (--turnosParaItens <= 0) {
        int linha = std::rand() % mapa->getLinhas();
        int coluna = std::rand() % mapa->getColunas();
        adicionarItem(new Item(linha, coluna, "Surpresa", 20));
        turnosParaItens = 10;
    }

    // Geração de novas caravanas bárbaras
    if (--turnosParaBarbaros <= 0) {
        int linha = std::rand() % mapa->getLinhas();
        int coluna = std::rand() % mapa->getColunas();
        CaravanaBarbara* novaBarbara = new CaravanaBarbara(linha, coluna);
        adicionarCaravana(novaBarbara);
        turnosParaBarbaros = 15;
    }

    // Verificar e processar combates
    verificarCombates();

    mapa->imprimirMapa();
}

void Comandos::verificarCombates() {
    for (size_t i = 0; i < caravanas.size(); ++i) {
        for (size_t j = i + 1; j < caravanas.size(); ++j) {
            Caravana* caravana1 = caravanas[i];
            Caravana* caravana2 = caravanas[j];

            if ((abs(caravana1->getLinha() - caravana2->getLinha()) <= 1) &&
                (abs(caravana1->getColuna() - caravana2->getColuna()) <= 1)) {

                if (caravana1->getTipo() == "Bárbara" || caravana2->getTipo() == "Bárbara") {
                    // Sorteia o dano infligido
                    int dano = std::rand() % 10 + 1;
                    caravana1->sofrerDano(dano);
                    caravana2->sofrerDano(dano);
                    std::cout << "Combate entre " << caravana1->getTipo() << " e " << caravana2->getTipo() << ". Dano infligido: " << dano << std::endl;

                    // Remover caravanas destruídas
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
                mapa->atualizarPosicao(novaLinha, novaColuna, 'A'); // A de areia
            }
        }
    }
}


int Comandos::getNumeroCaravanas() const {
    return caravanas.size();
}

Caravana* Comandos::getCaravana(int id) {
    if (id < 0 || id >= caravanas.size()) {
        throw std::out_of_range("ID de caravana inválido.");
    }
    return caravanas[id];
}