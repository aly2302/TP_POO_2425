#include "ExecComandos.h"
#include <fstream>
#include <iostream>
#include <sstream>

void executarComandosDeFicheiro(const std::string& nomeFicheiro, Mapa* mapa, Buffer* buffer, bool& segunda_fase) {
    std::ifstream ficheiro(nomeFicheiro);

    if (!ficheiro.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o ficheiro " << nomeFicheiro << "." << std::endl;
        return;
    }

    std::string linha;
    while (std::getline(ficheiro, linha)) {
        if (linha.empty()) continue; // Ignorar linhas vazias

        std::istringstream iss(linha);
        std::string comando;
        iss >> comando;

        if (segunda_fase) {
            if (comando == "comprac") {
                std::string cidade, tipoCaravana;
                if (iss >> cidade >> tipoCaravana) {
                    mapa->comprarCaravanaCidade(cidade, tipoCaravana);
                } else {
                    std::cerr << "Erro: Parâmetros inválidos no comando 'comprac'." << std::endl;
                }
            } else if (comando == "cidade") {
                std::string cidade;
                if (iss >> cidade) {
                    mapa->listarCidade(cidade);
                } else {
                    std::cerr << "Erro: Nome da cidade não fornecido no comando 'cidade'." << std::endl;
                }
            } else if (comando == "caravana") {
                int idCaravana;
                if (iss >> idCaravana) {
                    mapa->listarCaravana(idCaravana);
                } else {
                    std::cerr << "Erro: ID da caravana inválido no comando 'caravana'." << std::endl;
                }
            } else if (comando == "compra") {
                int idCaravana, toneladas;
                if (iss >> idCaravana >> toneladas) {
                    mapa->comprarMercadoria(idCaravana, toneladas);
                } else {
                    std::cerr << "Erro: Parâmetros inválidos no comando 'compra'." << std::endl;
                }
            } else if (comando == "vende") {
                int idCaravana;
                if (iss >> idCaravana) {
                    mapa->venderMercadoria(idCaravana);
                } else {
                    std::cerr << "Erro: ID da caravana inválido no comando 'vende'." << std::endl;
                }
            } else if (comando == "move") {
                int idCaravana;
                std::string posicao;
                if (iss >> idCaravana >> posicao) {
                    try {
                        mapa->moverCaravana(idCaravana, posicao);
                        std::cout << "Comando 'move' executado: Caravana " << idCaravana << " movida para " << posicao << ".\n";
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao mover caravana: " << e.what() << std::endl;
                    }
                } else {
                    std::cerr << "Erro: Parâmetros inválidos no comando 'move'." << std::endl;
                }
            } else if (comando == "caravanas_list") {
                mapa->listarCaravanas();
            } else if (comando == "cidades_list") {
                mapa->listarCidades();
            } else if (comando == "terminar") {
                std::cout << "Comando: terminar. Finalizando execução dos comandos..." << std::endl;
                break;
            } else if (comando == "saves") {
                std::string nome;
                iss >> nome;
                if (!nome.empty()) {
                    mapa->salvarEstado(nome);
                } else {
                    std::cerr << "Erro: Nome do estado não fornecido no comando 'saves'." << std::endl;
                }
            } else if (comando == "loads") {
                std::string nome;
                iss >> nome;
                if (!nome.empty()) {
                    mapa->carregarEstado(nome);
                } else {
                    std::cerr << "Erro: Nome do estado não fornecido no comando 'loads'." << std::endl;
                }
            } else if (comando == "lists") {
                mapa->listarEstadosSalvos();
            } else if (comando == "dels") {
                std::string nome;
                iss >> nome;
                if (!nome.empty()) {
                    mapa->apagarEstadoSalvo(nome);
                } else {
                    std::cerr << "Erro: Nome do estado não fornecido no comando 'dels'." << std::endl;
                }
            } else if (comando == "auto") {
                int idCaravana;
                if (iss >> idCaravana) {
                    mapa->ativarAutoMover(idCaravana);
                } else {
                    std::cerr << "Erro: ID da caravana inválido no comando 'auto'." << std::endl;
                }
            } else if (comando == "stop") {
                int idCaravana;
                if (iss >> idCaravana) {
                    mapa->desativarAutoMover(idCaravana);
                } else {
                    std::cerr << "Erro: ID da caravana inválido no comando 'stop'." << std::endl;
                }
            } else if (comando == "prox") {
                int instantes = 1; // Valor padrão
                if (iss >> instantes && instantes > 0) {
                    mapa->executarInstantes(instantes);
                } else {
                    mapa->executarInstantes(instantes); // Avança um instante por padrão
                }
            } else if (comando == "barbaro") {
                int x, y;
                if (iss >> x >> y) {
                    mapa->adicionarCaravanaBarbara(x, y);
                } else {
                    std::cerr << "Erro: Parâmetros inválidos no comando 'barbaro'." << std::endl;
                }
            } else if (comando == "areia") {
                int linha, coluna, raio;
                if (iss >> linha >> coluna >> raio) {
                    mapa->criarTempestadeAreia(linha, coluna, raio);
                } else {
                    std::cerr << "Erro: Parâmetros inválidos no comando 'areia'." << std::endl;
                }
            } else if (comando == "moedas") {
                int moedas;
                if (iss >> moedas) {
                    mapa->addMoedas(moedas);
                } else {
                    std::cerr << "Erro: Valor inválido no comando 'moedas'." << std::endl;
                }
            } else if (comando == "tripul") {
                int idCaravana, quantidade;
                if (iss >> idCaravana >> quantidade) {
                    mapa->contratarTripulantes(idCaravana, quantidade);
                } else {
                    std::cerr << "Erro: Parâmetros inválidos no comando 'tripul'." << std::endl;
                }
            } else {
                std::cerr << "Comando desconhecido: " << comando << std::endl;
            }
        } else {
            std::cerr << "Comando inválido fora da segunda fase: " << comando << std::endl;
        }
    }

    ficheiro.close();
    std::cout << "Execução de comandos do ficheiro " << nomeFicheiro << " concluída." << std::endl;
}
