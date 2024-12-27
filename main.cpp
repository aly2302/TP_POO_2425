#include "Mapa.h"
#include <iostream>
#include <sstream>

//testar código

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

        std::string input; // Variável para armazenar a entrada do utilizador
        std::string comando; // Variável para armazenar o comando
        std::string nomeFicheiro; // Variável para armazenar o nome do ficheiro
        std::string var1; // Variável para armazenar a var1
        std::string var2; // Variável para armazenar a var2
        std::string var3; // Variável para armazenar a var3


        bool executando = true;
        bool segunda_fase = false;
        while (executando) {
            //exibirMenu();
            std::cout << "Escolha um comando: ";
            std::getline(std::cin, input); // Lê a linha toda

            std::istringstream iss(input); // Cria um fluxo de string a partir da entrada
            iss >> comando; // Extrai o comando

            if(!segunda_fase){
                if (comando == "config") { // Verifica se o comando é "config" (config <nomeFicheiro>)
                    iss >> nomeFicheiro; // Extrai o nome do ficheiro
                    if (!nomeFicheiro.empty()) { // Verifica se o nome do ficheiro não está vazio
                        std::cout << "Comando: " << comando << ", Nome do Ficheiro: " << nomeFicheiro << std::endl;
                        Mapa mapa(nomeFicheiro, &buffer); // Cria um objeto Mapa com o nome do ficheiro
                        mapa.imprimirMapa();
                        segunda_fase = true;
                    } else {
                        std::cout << "Erro: Nome do ficheiro não fornecido." << std::endl; // Mensagem de erro se o nome do ficheiro estiver vazio
                    }
                } else if (comando == "sair") { // Verifica se o comando é "sair"
                    executando = false;
                    std::cout << "Encerrando o programa..." << std::endl;
                    break;
                } else {
                    std::cout << "Comando desconhecido." << std::endl; // Mensagem de erro se o comando não for reconhecido
                }
            }else{

                if (comando == "exec") { // Verifica se o comando é "config" (exec <nomeFicheiro>)
                    iss >> nomeFicheiro; // Extrai o nome do ficheiro
                    if (!nomeFicheiro.empty()) { // Verifica se o nome do ficheiro não está vazio
                        std::cout << "Comando: " << comando << ", Nome do Ficheiro: " << nomeFicheiro << std::endl;

                    } else {
                        std::cout << "Erro: Nome do ficheiro não fornecido." << std::endl; // Mensagem de erro se o nome do ficheiro estiver vazio
                    }
                } else if (comando == "prox") { // Verifica se o comando é "prox" (prox <n>)
                    int instances = 1; // Valor padrão
                    if (iss >> var1) { // Tenta extrair um valor extra
                        instances = std::stoi(var1); // Converte a string para int
                        if (instances <= 0) { // Verifica se o valor é menor or igual a 0
                            std::cout << "Erro: O valor de 'n' deve ser maior que 0." << std::endl;
                        }
                        std::cout << "Comando: " << comando << ", n: " << instances << std::endl;
                    } else {
                        std::cout << "Comando: " << comando << ", n: " << instances << std::endl; // Se não houver valor extra, usa o padrão
                    }
                }else if (comando == "comprac") { // Verifica se o comando é "comprac" (comprac <C> <T>)
                    iss >> var1; // Extrai a cidade
                    if (!var1.empty()) { // Verifica se o nome da cidade não está vazio
                        iss >> var2; // Extrai a Caravana
                        if (!var2.empty()) { // Verifica se o nome da caravana não está vazio
                            std::cout << "Comando: " << comando << ", Cidade: " << var1 << ", Caravana: " << var2 << std::endl;
                        }
                    } else {
                        std::cout << "Erro: Nome da cidade não fornecido." << std::endl; // Mensagem de erro se o nome da cidade estiver vazio
                    }
                }else if (comando == "precos") { // Verifica se o comando é "precos"
                    std::cout << "Comando: " << comando << std::endl;
                }else if (comando == "cidade") { // Verifica se o comando é "cidade" (cidade <C>)
                    iss >> var1; // Extrai a cidade
                    if (!var1.empty()) { // Verifica se o nome da cidade não está vazio
                        std::cout << "Comando: " << comando << ", Cidade: " << var1 << std::endl;
                    } else {
                        std::cout << "Erro: Nome da Cidade não fornecido." << std::endl; // Mensagem de erro se o nome da cidade estiver vazio
                    }
                }else if (comando == "caravana") { // Verifica se o comando é "caravana" (caravana <C>)
                    int n_caravana = 0;
                    iss >> var1; // Extrai o número da caravana
                    if (!var1.empty()) { // Verifica se o nome da cidade não está vazio
                        n_caravana = std::stoi(var1); // Converte a string para int
                        std::cout << "Comando: " << comando << ", Nº da caravana: " << n_caravana << std::endl;
                    } else {
                        std::cout << "Erro: Número da Caravana não fornecido." << std::endl; // Mensagem de erro se o nome da cidade estiver vazio
                    }
                }else if (comando == "compra") { // Verifica se o comando é "compra" (compra <N> <M>)
                    int n_caravana = 0;
                    int n_toneladas = 0;
                    iss >> var1; // Extrai o número da caravana
                    if (!var1.empty()) { // Verifica se o número da caravana não está vazio
                        n_caravana = std::stoi(var1); // Converte a string para int
                        iss >> var2; // Extrai as Toneladas
                        n_toneladas = std::stoi(var2); // Converte a string para int
                        if (!var2.empty()) { // Verifica se o valor das Toneladas não está vazio
                            std::cout << "Comando: " << comando << ", Número da Caravana: " << n_caravana << ", Toneladas: " << n_toneladas << std::endl;
                        }else {
                            std::cout << "Erro: Nº de Toneladas não fornecido." << std::endl; // Mensagem de erro se o nº de Toneladas estiver vazio
                        }
                    } else {
                        std::cout << "Erro: Número da Caravana não fornecido." << std::endl; // Mensagem de erro se o número da caravana estiver vazio
                    }
                }else if (comando == "vende") { // Verifica se o comando é "vende" (vende <N>)
                    int n_caravana = 0;
                    iss >> var1; // Extrai o número da caravana
                    if (!var1.empty()) { // Verifica se o número da caravana não está vazio
                        n_caravana = std::stoi(var1); // Converte a string para int
                        std::cout << "Comando: " << comando << ", Nº da Caravana: " << n_caravana << std::endl;
                    } else {
                        std::cout << "Erro: Nº da Caravana não fornecido." << std::endl; // Mensagem de erro se o número da caravana estiver vazio
                    }
                }else if (comando == "move") { // Verifica se o comando é "move" (move <N> <X>)
                    int n_caravana = 0;
                    iss >> var1; // Extrai o número da caravana
                    if (!var1.empty()) { // Verifica se o número da caravana não está vazio
                        n_caravana = std::stoi(var1); // Converte a string para int
                        iss >> var2; // Extrai a posicao
                        if (!var2.empty()) { // Verifica se a posição não está vazio
                            std::cout << "Comando: " << comando << ", Número da Caravana: " << n_caravana << ", Posição: " << var2 << std::endl;
                        }else {
                            std::cout << "Erro: Posição não fornecido." << std::endl; // Mensagem de erro se a posição estiver vazio
                        }
                    } else {
                        std::cout << "Erro: Nº da Caravana não fornecido." << std::endl; // Mensagem de erro se o número da caravana estiver vazio
                    }
                }else if (comando == "auto") { // Verifica se o comando é "auto" (auto <N>)
                    int n_caravana = 0;
                    iss >> var1; // Extrai o número da caravana
                    if (!var1.empty()) { // Verifica se o número da caravana não está vazio
                        n_caravana = std::stoi(var1); // Converte a string para int
                        std::cout << "Comando: " << comando << ", Nº da Caravana: " << n_caravana << std::endl;
                    } else {
                        std::cout << "Erro: Nº da Caravana não fornecido." << std::endl; // Mensagem de erro se o número da caravana estiver vazio
                    }
                }else if (comando == "stop") { // Verifica se o comando é "stop" (stop <N>)
                    int n_caravana = 0;
                    iss >> var1; // Extrai o número da caravana
                    if (!var1.empty()) { // Verifica se o número da caravana não está vazio
                        n_caravana = std::stoi(var1); // Converte a string para int
                        std::cout << "Comando: " << comando << ", Nº da Caravana: " << n_caravana << std::endl;
                    } else {
                        std::cout << "Erro: Nº da Caravana não fornecido." << std::endl; // Mensagem de erro se o número da caravana estiver vazio
                    }
                }else if (comando == "barbaro") { // Verifica se o comando é "barbaro" (barbaro <l> <c>)
                    int x = 0;
                    int y = 0;
                    iss >> var1; // Extrai a linha
                    if (!var1.empty()) { // Verifica se o valor da linha não está vazio
                        x = std::stoi(var1); // Converte a string para int
                        iss >> var2; // Extrai a coluna
                        if (!var2.empty()) { // Verifica se o valor da coluna não está vazio
                            y = std::stoi(var2); // Converte a string para int
                            std::cout << "Comando: " << comando << ", Linha: " << x << ", Coluna: " << y << std::endl;
                        } else {
                            std::cout << "Erro: O valor da Coluna não fornecido." << std::endl; // Mensagem de erro se o valor da coluna estiver vazio
                        }
                    } else {
                        std::cout << "Erro: O valor da Linha não fornecido." << std::endl; // Mensagem de erro se o valor da linha estiver vazio
                    }
                }else if (comando == "areia") { // Verifica se o comando é "areia" (areia <l> <c> <r>)
                    int x = 0;
                    int y = 0;
                    int r = 0;
                    iss >> var1; // Extrai a linha
                    if (!var1.empty()) { // Verifica se o valor da linha não está vazio
                        x = std::stoi(var1); // Converte a string para int
                        iss >> var2; // Extrai a coluna
                        if (!var2.empty()) { // Verifica se o valor da coluna não está vazio
                            y = std::stoi(var2); // Converte a string para int
                            iss >> var3; // Extrai o raio
                            if (!var3.empty()) { // Verifica se o valor do raio não está vazio
                                std::cout << "Comando: " << comando << ", Linha: " << x << ", Coluna: " << y << ", Raio: " << r << std::endl;
                            }else{
                                std::cout << "Erro: O valor do Raio não fornecido." << std::endl; // Mensagem de erro se o valor do raio estiver vazio
                            }
                        } else {
                            std::cout << "Erro: O valor da Coluna não fornecido." << std::endl; // Mensagem de erro se o valor da coluna estiver vazio
                        }
                    } else {
                        std::cout << "Erro: O valor da Linha não fornecido." << std::endl; // Mensagem de erro se o valor da linha estiver vazio
                    }
                }else if (comando == "moedas") { // Verifica se o comando é "moedas" (moedas <N>)
                    int moedas = 0;
                    iss >> var1; // Extrai o número de moedas
                    moedas = std::stoi(var1); // Converte a string para int
                    if (!var1.empty()) { // Verifica se o número de moedas não está vazio
                        std::cout << "Comando: " << comando << ", Moedas: " << moedas << std::endl;
                    } else {
                        std::cout << "Erro: Nº de Moedas não fornecido." << std::endl; // Mensagem de erro se o número de moedas estiver vazio
                    }
                }else if (comando == "tripul") { // Verifica se o comando é "tripul" (tripul <N> <T>)
                    int n_tripulacao = 0;
                    int n_caravana = 0;
                    iss >> var1; // Extrai o número da tripulação
                    if (!var1.empty()) { // Verifica se o número da tripulação não está vazio
                        n_tripulacao = std::stoi(var1); // Converte a string para int
                        iss >> var2; // Extrai o número da caravana
                        if (!var2.empty()) { // Verifica se o número da tripulação não está vazio
                            n_caravana = std::stoi(var2); // Converte a string para int
                            std::cout << "Comando: " << comando << ", Nº da Tripulação: " << n_tripulacao << ", Nº da Caravana: " << n_caravana << std::endl;
                        } else {
                            std::cout << "Erro: Nº da Caravana não fornecido." << std::endl; // Mensagem de erro se o número da caravana estiver vazio
                        }
                    } else {
                        std::cout << "Erro: Nº da Tripulação não fornecido." << std::endl; // Mensagem de erro se o número da tripulação estiver vazio
                    }
                }else if (comando == "saves") { // Verifica se o comando é "saves" (saves <nome>)
                    iss >> var1; // Extrai o nome
                    if (!var1.empty()) { // Verifica se o nome do ficheiro não está vazio
                        std::cout << "Comando: " << comando << ", Nome: " << var1 << std::endl;
                    } else {
                        std::cout << "Erro: Nome não fornecido." << std::endl; // Mensagem de erro se o nome estiver vazio
                    }
                }else if (comando == "loads") { // Verifica se o comando é "loads" (loads <nome>)
                    iss >> var1; // Extrai o nome
                    if (!var1.empty()) { // Verifica se o nome não está vazio
                        std::cout << "Comando: " << comando << ", Nome: " << var1 << std::endl;
                    } else {
                        std::cout << "Erro: Nome não fornecido." << std::endl; // Mensagem de erro se o nome estiver vazio
                    }
                }else if (comando == "lists") { // Verifica se o comando é "lists"
                    std::cout << "Comando: " << comando << std::endl;
                }else if (comando == "dels") { // Verifica se o comando é "dels" (dels <nome>)
                    iss >> var1; // Extrai o número da tripulação
                    if (!var1.empty()) { // Verifica se o nome não está vazio
                        std::cout << "Comando: " << comando << ", Nome: " << var1 << std::endl;
                    } else {
                        std::cout << "Erro: Nome não fornecido." << std::endl; // Mensagem de erro se o nome estiver vazio
                    }
                }else if (comando == "terminar") { // Verifica se o comando é "terminar"
                    executando = false;
                    std::cout << "Terminando o programa..." << std::endl;
                    break;
                }else {
                    std::cout << "Comando desconhecido." << std::endl; // Mensagem de erro se o comando não for reconhecido
                }
            }

           /* switch (comando) {
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
            */
        }

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
