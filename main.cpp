#include "Mapa.h"
#include <iostream>

void exibirMenu() {
    std::cout << "\nComandos disponíveis:" << std::endl;
    std::cout << "1. Criar caravana de comércio" << std::endl;
    std::cout << "2. Criar caravana militar" << std::endl;
    std::cout << "3. Criar caravana secreta" << std::endl;
    std::cout << "4. Mover caravana" << std::endl;
    std::cout << "5. Listar cidades" << std::endl;
    std::cout << "6. Exibir mapa" << std::endl;
    std::cout << "7. Executar simulação" << std::endl;
    std::cout << "8. Sair" << std::endl;
}

int main() {
    try {
        Buffer buffer(10, 20); // Dimensões do buffer
        Mapa mapa("config.txt", &buffer);

        bool executando = true;
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
                    mapa.adicionarCaravana(std::make_unique<CaravanaComercio>(mapa.gerarIDCaravana(), linha, coluna));
                    break;
                }
                case 2: {
                    int linha, coluna;
                    std::cout << "Informe a posição inicial (linha coluna): ";
                    std::cin >> linha >> coluna;
                    mapa.adicionarCaravana(std::make_unique<CaravanaMilitar>(mapa.gerarIDCaravana(), linha, coluna));
                    break;
                }
                case 3: {
                    int linha, coluna;
                    std::cout << "Informe a posição inicial (linha coluna): ";
                    std::cin >> linha >> coluna;
                    mapa.adicionarCaravana(std::make_unique<CaravanaSecreta>(mapa.gerarIDCaravana(), linha, coluna));
                    break;
                }
                case 4: {
                    int id, novaLinha, novaColuna;
                    std::cout << "Informe o ID da caravana e a nova posição (linha coluna): ";
                    std::cin >> id >> novaLinha >> novaColuna;
                    mapa.moverCaravana(id, novaLinha, novaColuna);
                    break;
                }
                case 5:
                    mapa.listarCidades();
                    break;
                case 6:
                    mapa.imprimirMapa();
                    break;
                case 7:
                    //mapa.executarSimulacao();
                    break;
                case 8:
                    executando = false;
                    std::cout << "Encerrando o programa..." << std::endl;
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
