#include "Mapa.h"
#include "Caravana.h"
#include "Comandos.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    // Fase 1: Configuração Inicial
    std::string ficheiroConfiguracao;
    std::cout << "Insira o nome do ficheiro de configuração: ";
    std::cin >> ficheiroConfiguracao;

    // Tenta abrir o ficheiro de configuração
    std::ifstream configFile(ficheiroConfiguracao);
    if (!configFile) {
        std::cerr << "Erro ao abrir o ficheiro de configuração." << std::endl;
        return 1;
    }

    // Inicializa o mapa a partir do ficheiro de configuração
    Mapa mapa(ficheiroConfiguracao);
    Comandos comandos(&mapa);

    // Leitura do ficheiro de configuração para adicionar caravanas
    std::string linha;
    while (std::getline(configFile, linha)) {
        std::istringstream iss(linha);
        std::string palavra;
        iss >> palavra;

        if (palavra == "caravana") {
            std::string tipo;
            int linha, coluna;
            iss >> tipo >> linha >> coluna;

            if (tipo == "comercio") {
                CaravanaComercio* caravana = new CaravanaComercio(linha, coluna);
                comandos.adicionarCaravana(caravana);
                mapa.atualizarPosicao(linha, coluna, 'C');
            } else if (tipo == "militar") {
                CaravanaMilitar* caravana = new CaravanaMilitar(linha, coluna);
                comandos.adicionarCaravana(caravana);
                mapa.atualizarPosicao(linha, coluna, 'M');
            } else if (tipo == "barbara") {
                CaravanaBarbara* caravana = new CaravanaBarbara(linha, coluna);
                comandos.adicionarCaravana(caravana);
                mapa.atualizarPosicao(linha, coluna, 'B');
            } else {
                std::cerr << "Tipo de caravana desconhecido: " << tipo << std::endl;
            }
        }
    }

    // Fase 2: Desenrolar da Simulação
    while (true) {
        // 1. Apresentação do estado atual
        std::cout << "\nEstado atual do mapa:\n";
        mapa.imprimirMapa();

        // 2. Leitura e execução de comandos do utilizador
        std::cout << "\nInsira os comandos (termina com 'prox' para avançar turno):\n";
        std::string comando;
        while (true) {
            std::getline(std::cin, comando);
            if (comando == "prox") {
                break;
            }
            try {
                comandos.interpretarComando(comando);
                // Atualiza a posição da caravana no mapa após o comando
                if (comando.find("move") != std::string::npos) {
                    int id, novaLinha, novaColuna;
                    std::istringstream iss(comando);
                    std::string palavra;
                    iss >> palavra >> id >> novaLinha >> novaColuna;
                    if (id >= 0 && id < comandos.getNumeroCaravanas()) {
                        Caravana* caravana = comandos.getCaravana(id);
                        mapa.atualizarPosicao(caravana->getLinha(), caravana->getColuna(), '.'); // Limpa posição antiga
                        caravana->mover(novaLinha, novaColuna);
                        char simbolo;
                        if (caravana->getTipo() == "comercio") {
                            simbolo = 'C';
                        } else if (caravana->getTipo() == "militar") {
                            simbolo = 'M';
                        } else if (caravana->getTipo() == "barbara") {
                            simbolo = 'B';
                        } else {
                            simbolo = '?'; // Simbolo de erro caso não se conheça o tipo
                        }
                        mapa.atualizarPosicao(novaLinha, novaColuna, simbolo);
                    } else {
                        std::cerr << "ID de caravana inválido." << std::endl;
                    }
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Erro: " << e.what() << std::endl;
            }
        }

        // 3. Execução de comportamentos automáticos
        comandos.processarTurno();
    }

    return 0;
}
