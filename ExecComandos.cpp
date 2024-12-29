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
            if (comando == "precos") {
                std::cout << "Executando comando: precos" << std::endl;
                mapa->listagem_precos();
            } else if (comando == "cidade") {
                std::string cidade;
                iss >> cidade;
                if (!cidade.empty()) {
                    std::cout << "Executando comando: cidade " << cidade << std::endl;
                    mapa->listarCidade(cidade);
                } else {
                    std::cerr << "Erro: Nome da cidade não fornecido no comando 'cidade'." << std::endl;
                }
            } else if (comando == "caravana") {
                int nCaravana;
                iss >> nCaravana;
                if (iss) {
                    std::cout << "Executando comando: caravana " << nCaravana << std::endl;
                    mapa->listarCaravana(nCaravana);
                } else {
                    std::cerr << "Erro: Número da caravana não fornecido no comando 'caravana'." << std::endl;
                }
            } else if (comando == "vende") {
                int nCaravana;
                iss >> nCaravana;
                if (iss) {
                    std::cout << "Executando comando: vende " << nCaravana << std::endl;
                    mapa->venderMercadoria(nCaravana);
                } else {
                    std::cerr << "Erro: Número da caravana não fornecido no comando 'vende'." << std::endl;
                }
            } else if (comando == "move") {
                int nCaravana;
                std::string direcao;
                iss >> nCaravana >> direcao;
                if (iss && !direcao.empty()) {
                    std::cout << "Executando comando: move " << nCaravana << " " << direcao << std::endl;
                    mapa->moverCaravana(nCaravana, direcao);
                } else {
                    std::cerr << "Erro: Argumentos insuficientes no comando 'move'." << std::endl;
                }
            } else if (comando == "caravanas_list") {
                std::cout << "Executando comando: caravanas_list" << std::endl;
                mapa->listarCaravanas();
            } else if (comando == "cidades_list") {
                std::cout << "Executando comando: cidades_list" << std::endl;
                mapa->listarCidades();
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
