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

int main() {
    try {
        Buffer buffer(10, 20); // Inicializar o buffer com dimensões apropriadas
        Mapa mapa("config.txt", &buffer); // Passar o buffer ao mapa

        bool executando = true;

        while (executando) {
            exibirMenu();
            int comando;
            std::cout << "Escolha um comando: ";
            std::cin >> comando;

            switch (comando) {
                case 1: {
                    int linha, coluna;
                    if (mapa.reduzirMoedas(mapa.getPrecoCaravana())) {
                        std::cout << "Informe a posição inicial (linha coluna): ";
                        std::cin >> linha >> coluna;
                        int id = mapa.gerarIDCaravana();
                        try {
                            mapa.adicionarCaravana(std::make_unique<CaravanaComercio>(id, linha, coluna));
                            std::cout << "Caravana do tipo Comércio adicionada na posição (" << linha << ", " << coluna << ")." << std::endl;
                        } catch (const std::exception& e) {
                            std::cerr << e.what() << std::endl;
                        }
                    } else {
                        std::cout << "Moedas insuficientes para criar uma caravana!" << std::endl;
                    }
                    break;
                }
                case 2: {
                    int linha, coluna;
                    if (mapa.reduzirMoedas(mapa.getPrecoCaravana())) {
                        std::cout << "Informe a posição inicial (linha coluna): ";
                        std::cin >> linha >> coluna;
                        int id = mapa.gerarIDCaravana();
                        try {
                            mapa.adicionarCaravana(std::make_unique<CaravanaMilitar>(id, linha, coluna));
                            std::cout << "Caravana do tipo Militar adicionada na posição (" << linha << ", " << coluna << ")." << std::endl;
                        } catch (const std::exception& e) {
                            std::cerr << e.what() << std::endl;
                        }
                    } else {
                        std::cout << "Moedas insuficientes para criar uma caravana!" << std::endl;
                    }
                    break;
                }
                case 3: {
                    int linha, coluna;
                    if (mapa.reduzirMoedas(mapa.getPrecoCaravana())) {
                        std::cout << "Informe a posição inicial (linha coluna): ";
                        std::cin >> linha >> coluna;
                        int id = mapa.gerarIDCaravana();
                        try {
                            mapa.adicionarCaravana(std::make_unique<CaravanaSecreta>(id, linha, coluna));
                            std::cout << "Caravana do tipo Secreta adicionada na posição (" << linha << ", " << coluna << ")." << std::endl;
                        } catch (const std::exception& e) {
                            std::cerr << e.what() << std::endl;
                        }
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
                    mapa.executarSimulacao();
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

        std::cout << "Fim do programa." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}