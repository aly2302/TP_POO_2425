#include "Mapa.h"
#include "ExecComandos.h"
#include <iostream>
#include <sstream>


int main() {
    try {
        Buffer buffer(10, 20); // Dimensões do buffer

        std::string input; // Variável para armazenar a entrada do utilizador
        std::string comando; // Variável para armazenar o comando
        std::string nomeFicheiro; // Variável para armazenar o nome do ficheiro
        std::string var1; // Variável para armazenar a var1
        std::string var2; // Variável para armazenar a var2
        std::string var3; // Variável para armazenar a var3

        Mapa* mapa = nullptr;

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
                        mapa = new Mapa(nomeFicheiro, &buffer); // Cria um objeto Mapa com o nome do ficheiro
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
                        executarComandosDeFicheiro(nomeFicheiro, mapa, &buffer, segunda_fase);

                    } else {
                        std::cout << "Erro: Nome do ficheiro não fornecido." << std::endl; // Mensagem de erro se o nome do ficheiro estiver vazio
                    }
                }else if (comando == "comprac") { // Verifica se o comando é "comprac" (comprac <C> <T>)
                    iss >> var1; // Extrai a cidade
                    if (!var1.empty()) { // Verifica se o nome da cidade não está vazio
                        iss >> var2; // Extrai a Caravana
                        if (!var2.empty()) { // Verifica se o nome da caravana não está vazio
                            std::cout << "Comando: " << comando << ", Cidade: " << var1 << ", Caravana: " << var2 << std::endl;
                            mapa->comprarCaravanaCidade(var1, var2);
                        }
                    } else {
                        std::cout << "Erro: Nome da cidade não fornecido." << std::endl; // Mensagem de erro se o nome da cidade estiver vazio
                    }
                }else if (comando == "precos") { // Verifica se o comando é "precos"
                    std::cout << "Comando: " << comando << std::endl;
                    mapa->listagem_precos();
                }else if (comando == "cidade") { // Verifica se o comando é "cidade" (cidade <C>)
                    iss >> var1; // Extrai a cidade
                    if (!var1.empty()) { // Verifica se o nome da cidade não está vazio
                        std::cout << "Comando: " << comando << ", Cidade: " << var1 << std::endl;
                        mapa->listarCidade(var1);
                    } else {
                        std::cout << "Erro: Nome da Cidade não fornecido." << std::endl; // Mensagem de erro se o nome da cidade estiver vazio
                    }
                }else if (comando == "caravana") { // Verifica se o comando é "caravana" (caravana <C>)
                    int n_caravana = 0;
                    iss >> var1; // Extrai o número da caravana
                    if (!var1.empty()) { // Verifica se o nome da cidade não está vazio
                        n_caravana = std::stoi(var1); // Converte a string para int
                        std::cout << "Comando: " << comando << ", Nº da caravana: " << n_caravana << std::endl;
                        mapa->listarCaravana(n_caravana);

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
                            mapa->comprarMercadoria(n_caravana,n_toneladas);
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
                        mapa->venderMercadoria(n_caravana);
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
                            mapa->moverCaravana(n_caravana, var2);
                        }else {
                            std::cout << "Erro: Posição não fornecido." << std::endl; // Mensagem de erro se a posição estiver vazio
                        }
                    } else {
                        std::cout << "Erro: Nº da Caravana não fornecido." << std::endl; // Mensagem de erro se o número da caravana estiver vazio
                    }
                }else if (comando == "auto") {
                        int idCaravana;
                        if (iss >> idCaravana && mapa) {
                            mapa->ativarAutoMover(idCaravana);
                        } else {
                            std::cout << "Erro: ID da caravana inválido ou mapa não configurado.\n";
                        }
                    } else if (comando == "stop") {
                        int idCaravana;
                        if (iss >> idCaravana && mapa) {

                            mapa->desativarAutoMover(idCaravana);
                        } else {
                            std::cout << "Erro: ID da caravana inválido ou mapa não configurado.\n";
                        }
                    } else if (comando == "prox") {
                        int instantes = 1; // Valor padrão
                        if (iss >> instantes && instantes > 0 && mapa) {
                            mapa->executarInstantes(instantes);
                        } else if (mapa) {
                            mapa->executarInstantes(instantes); // Avança um instante por padrão
                        } else {
                            std::cout << "Erro: Valor de instantes inválido ou mapa não configurado.\n";
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
                }else if (comando == "areia") {
                    int linha, coluna, raio;
                    if (iss >> linha >> coluna >> raio && mapa) {
                        mapa->criarTempestadeAreia(linha, coluna, raio);
                    } else {
                        std::cout << "Erro: Parâmetros inválidos ou mapa não configurado.\n";
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
                }else if (comando == "tripul") { // Verifica se o comando é "tripul <N> <T>"
                int idCaravana, quantidade;
                if (iss >> idCaravana >> quantidade && mapa) {
                    mapa->contratarTripulantes(idCaravana, quantidade);
                } else {
                    std::cout << "Erro: Parâmetros inválidos ou mapa não configurado.\n";
                }
            }
            else if (comando == "saves") { // Verifica se o comando é "saves" (saves <nome>)
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
                }else if (comando == "caravanas_list") { // Verifica se o comando é "dels" (dels <nome>)
                    std::cout << "Comando: " << comando << ", Nome: " << var1 << std::endl;
                    mapa->listarCaravanas();

                }else if (comando == "cidades_list") { // Verifica se o comando é "dels" (dels <nome>)
                    std::cout << "Comando: " << comando << ", Nome: " << var1 << std::endl;
                    mapa->listarCidades();

                }else if (comando == "terminar") { // Verifica se o comando é "terminar"
                    executando = false;
                    std::cout << "Terminando o programa..." << std::endl;
                    break;
                }else {
                    std::cout << "Comando desconhecido." << std::endl; // Mensagem de erro se o comando não for reconhecido
                }
            }

            mapa->imprimirMapa();
        }

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}