#include "Mapa.h"
#include "Caravana.h"
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

void exibirMenu() {
    std::cout << "\nComandos disponíveis:" << std::endl;
    std::cout << "1. Criar caravana de comércio" << std::endl;
    std::cout << "2. Criar caravana militar" << std::endl;
    std::cout << "3. Criar caravana secreta" << std::endl;
    std::cout << "4. Mover caravana" << std::endl;
    std::cout << "5. Listar cidades" << std::endl;
    std::cout << "6. Exibir mapa" << std::endl;
    std::cout << "7. Iniciar simulação" << std::endl;
    std::cout << "8. Pausar simulação" << std::endl;
    std::cout << "9. Sair" << std::endl;
}

int main() {
    try {
        // Inicializar o mapa
        Mapa mapa("config.txt");

        bool executando = true;
        bool simulacaoAtiva = false;
        std::thread simulacaoThread;

        while (executando) {
            exibirMenu();
            int comando;
            std::cout << "Escolha um comando: ";
            std::cin >> comando;

            switch (comando) {
                case 1: {
                    int linha, coluna;
                    std::cout << "Informe a posição inicial (linha coluna): ";
                    std::cin >> linha >> coluna;
                    mapa.adicionarCaravana(std::make_unique<CaravanaComercio>(1, linha, coluna));
                    std::cout << "Caravana de comércio criada com sucesso!" << std::endl;
                    mapa.imprimirMapa(); // Exibir o mapa atualizado
                    break;
                }
                case 2: {
                    int linha, coluna;
                    std::cout << "Informe a posição inicial (linha coluna): ";
                    std::cin >> linha >> coluna;
                    mapa.adicionarCaravana(std::make_unique<CaravanaMilitar>(2, linha, coluna));
                    std::cout << "Caravana militar criada com sucesso!" << std::endl;
                    mapa.imprimirMapa(); // Exibir o mapa atualizado
                    break;
                }
                case 3: {
                    int linha, coluna;
                    std::cout << "Informe a posição inicial (linha coluna): ";
                    std::cin >> linha >> coluna;
                    mapa.adicionarCaravana(std::make_unique<CaravanaSecreta>(3, linha, coluna));
                    std::cout << "Caravana secreta criada com sucesso!" << std::endl;
                    mapa.imprimirMapa(); // Exibir o mapa atualizado
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
                    if (!simulacaoAtiva) {
                        simulacaoAtiva = true;
                        std::cout << "Iniciando simulação..." << std::endl;
                        simulacaoThread = std::thread([&]() {
                            while (simulacaoAtiva) {
                                mapa.executarSimulacao();
                                std::this_thread::sleep_for(std::chrono::seconds(1));
                            }
                        });
                    } else {
                        std::cout << "Simulação já está ativa!" << std::endl;
                    }
                    break;
                case 8:
                    if (simulacaoAtiva) {
                        simulacaoAtiva = false;
                        if (simulacaoThread.joinable()) {
                            simulacaoThread.join();
                        }
                        std::cout << "Simulação pausada." << std::endl;
                    } else {
                        std::cout << "A simulação não está ativa." << std::endl;
                    }
                    break;
                case 9:
                    std::cout << "Encerrando o programa..." << std::endl;
                    executando = false;
                    if (simulacaoAtiva) {
                        simulacaoAtiva = false;
                        if (simulacaoThread.joinable()) {
                            simulacaoThread.join();
                        }
                    }
                    break;
                default:
                    std::cout << "Comando inválido!" << std::endl;
                    break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
