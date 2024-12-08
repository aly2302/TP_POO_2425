#include "Mapa.h"
#include "Caravana.h"
#include "Buffer.h"
#include <iostream>
#include <memory>
#include <string>

void exibirMenu() {
    std::cout << "\nComandos disponíveis:" << std::endl;
    std::cout << "1. Criar caravana de comércio" << std::endl;
    std::cout << "2. Criar caravana militar" << std::endl;
    std::cout << "3. Criar caravana secreta" << std::endl;
    std::cout << "4. Mover caravana" << std::endl;
    std::cout << "5. Listar cidades" << std::endl;
    std::cout << "6. Exibir mapa" << std::endl;
    std::cout << "7. Executar simulação" << std::endl;
    std::cout << "8. Adicionar cidade" << std::endl;
    std::cout << "9. Sair" << std::endl;
}

int gerarIDCaravana() {
    static int idAtual = 0;
    return ++idAtual;
}

int main() {
    try {
        Buffer buffer(10, 20); // Inicializar o buffer com dimensões apropriadas
        Mapa mapa("config.txt", &buffer); // Passar o buffer ao mapa

        int moedas = mapa.getMoedas(); // Inicializar moedas do jogador
        int instantes = 0;             // Contador de instantes
        int combatesVencidos = 0;      // Contador de combates vencidos

        bool executando = true;

        while (executando) {
            if (moedas <= 0 && mapa.getNumeroCaravanas() == 0) {
                std::cout << "Você ficou sem moedas e sem caravanas. Fim da simulação!" << std::endl;
                break;
            }

            exibirMenu();
            int comando;
            std::cout << "Escolha um comando: ";
            std::cin >> comando;

            switch (comando) {
                case 1: {
                    int linha, coluna;
                    std::cout << "Informe a posição inicial (linha coluna): ";
                    std::cin >> linha >> coluna;
                    int id = gerarIDCaravana();
                    try {
                        mapa.adicionarCaravana(std::make_unique<CaravanaComercio>(id, linha, coluna));
                    } catch (const std::exception& e) {
                        std::cerr << e.what() << std::endl;
                    }
                    mapa.imprimirMapa(); // Exibir o mapa atualizado
                    break;
                }

                case 2: {
                    int linha, coluna, custo = mapa.getPrecoCaravana();
                    if (moedas >= custo) {
                        std::cout << "Informe a posição inicial (linha coluna): ";
                        std::cin >> linha >> coluna;
                        int id = gerarIDCaravana();
                        mapa.adicionarCaravana(std::make_unique<CaravanaMilitar>(id, linha, coluna));
                        moedas -= custo;
                        std::cout << "Caravana militar criada com sucesso! ID: " << id << std::endl;
                        std::cout << "Moedas restantes: " << moedas << std::endl;
                        mapa.imprimirMapa(); // Exibir o mapa atualizado
                    } else {
                        std::cout << "Moedas insuficientes para criar uma caravana!" << std::endl;
                    }
                    break;
                }
                case 3: {
                    int linha, coluna, custo = mapa.getPrecoCaravana();
                    if (moedas >= custo) {
                        std::cout << "Informe a posição inicial (linha coluna): ";
                        std::cin >> linha >> coluna;
                        int id = gerarIDCaravana();
                        mapa.adicionarCaravana(std::make_unique<CaravanaSecreta>(id, linha, coluna));
                        moedas -= custo;
                        std::cout << "Caravana secreta criada com sucesso! ID: " << id << std::endl;
                        std::cout << "Moedas restantes: " << moedas << std::endl;
                        mapa.imprimirMapa(); // Exibir o mapa atualizado
                    } else {
                        std::cout << "Moedas insuficientes para criar uma caravana!" << std::endl;
                    }
                    break;
                }
                case 4: {
                    int id, novaLinha, novaColuna;
                    std::cout << "Informe o ID da caravana e a nova posição (linha coluna): ";
                    std::cin >> id >> novaLinha >> novaColuna;
                    try {
                        mapa.moverCaravana(id, novaLinha, novaColuna);
                        std::cout << "Caravana movida com sucesso!" << std::endl;
                        mapa.imprimirMapa(); // Exibir o mapa atualizado
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao mover caravana: " << e.what() << std::endl;
                    }
                    break;
                }
                case 5:
                    std::cout << "Cidades no mapa:" << std::endl;
                    mapa.listarCidades();
                    break;
                case 6:
                    std::cout << "Estado atual do mapa:" << std::endl;
                    mapa.imprimirMapa();
                    break;
                case 7:
                    std::cout << "Executando simulação..." << std::endl;
                    for (int i = 0; i < 5; ++i) {
                        mapa.executarSimulacao();
                        instantes++;
                        /*
                        if (mapa.resolverCombates(combatesVencidos)) {
                            std::cout << "Combate resolvido!" << std::endl;
                        }
                         */
                    }
                    std::cout << "Simulação concluída." << std::endl;
                    break;
                case 8: {
                    int linha, coluna;
                    std::string nome;
                    std::cout << "Informe a posição da cidade (linha coluna): ";
                    std::cin >> linha >> coluna;
                    std::cout << "Informe o nome da cidade: ";
                    std::cin.ignore(); // Ignorar o \n restante
                    std::getline(std::cin, nome);
                    try {
                        mapa.adicionarCidade(Cidade(nome, linha, coluna));
                        std::cout << "Cidade \"" << nome << "\" adicionada com sucesso!" << std::endl;
                        mapa.imprimirMapa(); // Exibir o mapa atualizado
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao adicionar cidade: " << e.what() << std::endl;
                    }
                    break;
                }
                case 9:
                    std::cout << "Encerrando o programa..." << std::endl;
                    executando = false;
                    break;
                default:
                    std::cout << "Comando inválido!" << std::endl;
                    break;
            }
        }

        std::cout << "Resumo Final:\n";
        std::cout << "Instantes decorridos: " << instantes << std::endl;
        std::cout << "Combates vencidos: " << combatesVencidos << std::endl;
        std::cout << "Moedas restantes: " << moedas << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}