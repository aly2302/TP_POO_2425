// Mapa.cpp - Completo e otimizado
#include "Mapa.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <unordered_set>


Mapa::Mapa(const std::string& nomeFicheiro, Buffer* buffer) : buffer(buffer) {
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        throw std::runtime_error("Erro ao abrir o ficheiro do mapa.");
    }

    try {
        // Ler dimensões do mapa
        ficheiro >> linhas >> colunas;
        ficheiro.ignore();

        // Inicializar o grid
        grid = new char[linhas * colunas];
        for (int i = 0; i < linhas; ++i) {
            std::string linha;
            std::getline(ficheiro, linha);
            if (linha.size() != static_cast<size_t>(colunas)) {
                throw std::runtime_error("Linha do grid não corresponde ao número de colunas.");
            }
            for (int j = 0; j < colunas; ++j) {
                grid[i * colunas + j] = linha[j];
            }
        }

        std::srand(std::time(0));


        // Processar o grid para adicionar dados
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                char caracter = grid[i * colunas + j];

                // Verifica se o caractere é um número
                if (std::isdigit(caracter)) {
                    int id = gerarIDCaravana();  // Converte o caractere para o valor numérico
                    std::cout << "ID: " << id << std::endl;
                    // Adiciona uma caravana de comércio na posição correta
                    // Vetor com os nomes das caravanas
                    std::vector<std::string> caravanas = {"CaravanaComercio", "CaravanaMilitar", "CaravanaSecreta"};

                    // Seleciona aleatoriamente um tipo de caravana
                    std::string caravanaAleatoria = caravanas[std::rand() % caravanas.size()];

                    // Cria e adiciona a caravana aleatória
                    if (caravanaAleatoria == "CaravanaComercio") {
                        adicionarCaravana(std::make_unique<CaravanaComercio>(id, i, j));
                    } else if (caravanaAleatoria == "CaravanaMilitar") {
                        adicionarCaravana(std::make_unique<CaravanaMilitar>(id, i, j));
                    } else if (caravanaAleatoria == "CaravanaSecreta") {
                        adicionarCaravana(std::make_unique<CaravanaSecreta>(id, i, j));
                    }
                }
            }
        }

        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                char caracter = grid[i * colunas + j];

                // Verifica se o caractere é um '!' para caravana bárbara
                if (caracter == '!') {
                    // Adiciona uma caravana bárbara na posição correta
                    adicionarCaravana(std::make_unique<CaravanaBarbara>(gerarIDCaravana(), i, j));
                }
            }
        }



        // Processar o grid para adicionar as caravanas para venda nas cidades
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                char caracter = grid[i * colunas + j];

                if (std::isalpha(caracter)) {
                    adicionarCidade(std::make_unique<Cidade>(std::string(1, caracter), i, j, *this));
                }
            }
        }


        // Ler parâmetros adicionais
        std::string str1;
        ficheiro >> str1 >> moedas;
        ficheiro >> str1 >> instantesEntreNovosItens;
        ficheiro >> str1 >> duracaoItem;
        ficheiro >> str1 >> maxItens;
        ficheiro >> str1 >> precoVendaMercadoria;
        ficheiro >> str1 >> precoCompraMercadoria;
        ficheiro >> str1 >> precoCaravana;
        ficheiro >> str1 >> instantesEntreNovosBarbaros;
        ficheiro >> str1 >> duracaoBarbaros;

        std::srand(std::time(nullptr)); // Inicializa o gerador de números aleatórios

        ficheiro.close();
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Erro ao ler o ficheiro: ") + e.what());
    }
}

Mapa::~Mapa() {
    delete[] grid;
}

const std::vector<std::unique_ptr<Caravana>>& Mapa::getCaravanas() const {
    return caravanas;
}

void Mapa::listarCaravanas() const {
    for (const auto& caravana : caravanas) {
        std::cout << "ID: " << caravana->getId()
                  << ", Tipo: " << caravana->getTipo()
                  << ", Posição: (" << caravana->getLinha() << ", " << caravana->getColuna() << ")"
                  << std::endl;
    }
}

void Mapa::listarCaravana(int id) const {
    for (const auto& caravana : caravanas) {
        if(caravana->getId() == id){
            std::cout << "ID: " << caravana->getId()
                      << ", Tipo: " << caravana->getTipo()
                      << ", Posição: (" << caravana->getLinha() << ", " << caravana->getColuna() << ")"
                      << ", Capacidade Carga: " << caravana->getCapacidadeCarga()
                      << ", Capacidade Agua: " << caravana->getCapacidadeAgua()
                      << ", Tripulantes: " << caravana->getTripulantes()
                      << ", Agua Atual: " << caravana->getAguaAtual()
                      << ", Carga Atual: " << caravana->getCargaAtual()
                      << std::endl;
        }
    }
}

void Mapa::listarCidades() const {
    for (const auto& cidade : cidades) {
        cidade->imprimirDetalhes();
    }
}

void Mapa::listarCidade(const std::string& nome) const {
    for (const auto& cidade : cidades) {
        if (cidade->getNome() == nome) {
            cidade->imprimirDetalhes();
        }
    }
}

int Mapa::calcularIndice(int linha, int coluna) const {
    return linha * colunas + coluna;
}

int Mapa::getNumeroCaravanas() const {
    return caravanas.size();
}

bool Mapa::posicaoValida(int linha, int coluna) const {
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

void Mapa::atualizarGrid(int linha, int coluna, char simbolo) {
    if (!posicaoValida(linha, coluna)) {
        throw std::out_of_range("Posição inválida no mapa.");
    }
    grid[calcularIndice(linha, coluna)] = simbolo;
}

char Mapa::obterGrid(int linha, int coluna) const {
    if (!posicaoValida(linha, coluna)) {
        throw std::out_of_range("Posição inválida no mapa.");
    }
    return grid[calcularIndice(linha, coluna)];
}

void Mapa::imprimirMapa() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            // Acessa o caractere na posição (i, j) do grid
            std::cout << grid[i * colunas + j];  // Acesso direto usando a fórmula de índice
        }
        std::cout << std::endl;  // Nova linha após cada linha do grid
    }
}


bool Mapa::reduzirMoedas(int quantidade) {
    if (moedas >= quantidade) {
        moedas -= quantidade;
        return true;
    }
    return false;
}

bool Mapa::addMoedas(int quantidade) {
    if (moedas >= quantidade) {
        moedas += quantidade;
        std::cout << "O utilizador tem agora: " << moedas << " moedas." << std::endl;
        return true;
    }
    return false;
}

void Mapa::adicionarCaravana(std::unique_ptr<Caravana> caravana) {
    if (!posicaoValida(caravana->getLinha(), caravana->getColuna())) {
        throw std::out_of_range("Posição inválida para adicionar a caravana.");
    }
    /*
    // Usar o ID da caravana como símbolo no grid
    int id = caravana->getId();

    char simbolo = (id < 10) ? '0' + id : '*'; // Simbolo para IDs > 9
    atualizarGrid(caravana->getLinha(), caravana->getColuna(), simbolo);
    */
    caravanas.push_back(std::move(caravana)); // Adiciona a caravana à lista
}


void Mapa::moverCaravana(int id, const std::string& direcao) {
    for (auto& caravana : caravanas) {
        if (caravana->getId() == id) {
            int linhaAtual = caravana->getLinha();
            int colunaAtual = caravana->getColuna();

            // Determinar nova posição com base na direção
            int novaLinha = linhaAtual;
            int novaColuna = colunaAtual;

            if (direcao == "D") { // Direita
                novaColuna++;
            } else if (direcao == "E") { // Esquerda
                novaColuna--;
            } else if (direcao == "C") { // Cima
                novaLinha--;
            } else if (direcao == "B") { // Baixo
                novaLinha++;
            } else if (direcao == "CE") { // Cima-Esquerda
                novaLinha--;
                novaColuna--;
            } else if (direcao == "CD") { // Cima-Direita
                novaLinha--;
                novaColuna++;
            } else if (direcao == "BE") { // Baixo-Esquerda
                novaLinha++;
                novaColuna--;
            } else if (direcao == "BD") { // Baixo-Direita
                novaLinha++;
                novaColuna++;
            } else {
                throw std::invalid_argument("Direção inválida. Use D, E, C, B, CE, CD, BE ou BD.");
            }

            // Verificar se a posição é válida
            if (!posicaoValida(novaLinha, novaColuna)) {
                throw std::out_of_range("Posição inválida para mover a caravana.");
            }

            bool estacidade = false;
            bool vaicidade = false;

            for (const auto& cidade : cidades) {
                if (cidade->getLinha() == novaLinha && cidade->getColuna() == novaColuna) {
                    vaicidade = true;
                }
            }

            for (const auto& cidade : cidades) {
                if (cidade->getLinha() == linhaAtual && cidade->getColuna() == colunaAtual) {
                    estacidade = true;
                }
            }

            if(vaicidade){
                atualizarGrid(linhaAtual, colunaAtual, '.');
                caravana->moverPara(novaLinha, novaColuna);
            }else if(estacidade && obterGrid(novaLinha, novaColuna) != '+'){
                caravana->moverPara(novaLinha, novaColuna);
                char simbolo = (id < 10) ? '0' + id : '*'; // Representar IDs menores que 10 como números
                atualizarGrid(novaLinha, novaColuna, simbolo);
            }else if(obterGrid(novaLinha, novaColuna) != '+' && obterGrid(linhaAtual, colunaAtual) != '!' && caravana->getTipo() != "Barbara"){
                atualizarGrid(linhaAtual, colunaAtual, '.');
                caravana->moverPara(novaLinha, novaColuna);
                if(caravana->getTipo() == "Comercio"){
                    caravana->consumirAgua(caravana->calcularConsumoAguaComercio());
                }else if (caravana->getTipo() == "Militar"){
                    caravana->consumirAgua(caravana->calcularConsumoAguaMilitar());
                }
                char simbolo = (id < 10) ? '0' + id : '*'; // Representar IDs menores que 10 como números
                atualizarGrid(novaLinha, novaColuna, simbolo);
            }else if(obterGrid(novaLinha, novaColuna) != '+' && obterGrid(linhaAtual, colunaAtual) != '!' && caravana->getTipo() == "Barbara"){
                atualizarGrid(linhaAtual, colunaAtual, '.');
                caravana->moverPara(novaLinha, novaColuna);
                atualizarGrid(novaLinha, novaColuna, '!');
            }else if(obterGrid(novaLinha, novaColuna) != '+' && obterGrid(linhaAtual, colunaAtual) == '!'){
                atualizarGrid(linhaAtual, colunaAtual, '.');
                caravana->moverPara(novaLinha, novaColuna);
                atualizarGrid(novaLinha, novaColuna, '!');
            }
            return;
        }
    }
    throw std::runtime_error("Caravana com ID não encontrada.");
}

int Mapa::gerarIDCaravana() {
    static int idAtual = 0;
    return ++idAtual;
}


void Mapa::adicionarCidade(std::unique_ptr<Cidade> cidade) {
    if (!posicaoValida(cidade->getLinha(), cidade->getColuna())) {
        throw std::out_of_range("Posição inválida para adicionar uma cidade.");
    }
    cidades.push_back(std::move(cidade));
}

void Mapa::removerCaravana(int id) {
    auto it = std::remove_if(caravanas.begin(), caravanas.end(), [id](const std::unique_ptr<Caravana>& caravana) {
        return caravana->getId() == id;
    });

    if (it != caravanas.end()) {
        caravanas.erase(it, caravanas.end());
    }
}


std::pair<int, int> Mapa::gerarMovimentoAleatorio(int linha, int coluna) const {
    int movimento[] = {-1, 0, 1}; // Movement options: stay, up/down, left/right
    int novaLinha = linha + movimento[std::rand() % 3];
    int novaColuna = coluna + movimento[std::rand() % 3];
    if (posicaoValida(novaLinha, novaColuna)) {
        return {novaLinha, novaColuna};
    }
    return {linha, coluna}; // Return original position if invalid move
}


std::unordered_set<int> caravanasAuto;
void Mapa::ativarAutoMover(int idCaravana) {
    for (const auto& caravana : caravanas) {
        if (caravana->getId() == idCaravana) {
            if (caravanasAuto.find(idCaravana) == caravanasAuto.end()) {
                caravanasAuto.insert(idCaravana);
                std::cout << "Caravana " << idCaravana << " ativada para movimento automático.\n";
            } else {
                std::cout << "Caravana " << idCaravana << " já está em movimento automático.\n";
            }
            return;
        }
    }
    std::cout << "Erro: Caravana com ID " << idCaravana << " não encontrada.\n";
}


void Mapa::desativarAutoMover(int idCaravana) {
    if (caravanasAuto.erase(idCaravana)) {
        std::cout << "Caravana " << idCaravana << " parou o movimento automático.\n";
    } else {
        std::cout << "Caravana " << idCaravana << " não está em movimento automático.\n";
    }
}

void Mapa::processarMovimentosAutomaticos() {
    for (int idCaravana : caravanasAuto) {
        try {
            static const std::vector<std::string> direcoes = {"D", "E", "C", "B", "CE", "CD", "BE", "BD"};
            std::string direcaoAleatoria = direcoes[rand() % direcoes.size()];
            moverCaravana(idCaravana, direcaoAleatoria);
        } catch (const std::exception& e) {
            std::cout << "Erro ao mover automaticamente a caravana " << idCaravana << ": " << e.what() << std::endl;


        }
    }
}

void Mapa::processarCombates() {
    for (size_t i = 0; i < caravanas.size(); ++i) {
        for (size_t j = i + 1; j < caravanas.size(); ++j) {
            auto& caravanaA = caravanas[i];
            auto& caravanaB = caravanas[j];

            if (caravanaA && caravanaB &&
                estaAdjacente(caravanaA->getLinha(), caravanaA->getColuna(),
                              caravanaB->getLinha(), caravanaB->getColuna()) &&
                caravanaA->getTipo() != caravanaB->getTipo() &&
                (caravanaA->getTipo() == "Barbara" || caravanaB->getTipo() == "Barbara")) {

                int sorteioA = rand() % (caravanaA->getTripulantes() + 1);
                int sorteioB = rand() % (caravanaB->getTripulantes() + 1);

                if (sorteioA > sorteioB) {
                    resolverCombate(*caravanaA, *caravanaB);
                } else if (sorteioB > sorteioA) {
                    resolverCombate(*caravanaB, *caravanaA);
                }
            }
        }
    }
}

void Mapa::resolverCombate(Caravana& vencedora, Caravana& perdedora) {
    int tripulantesVencedor = vencedora.getTripulantes();
    int perdaVencedor = tripulantesVencedor * 0.2;
    int perdaPerdedor = perdaVencedor * 2;

    vencedora.removerTripulantes(perdaVencedor);
    perdedora.removerTripulantes(perdaPerdedor);

    if (perdedora.getTripulantes() <= 0) {
        vencedora.adicionarCarga(perdedora.getAguaAtual());
        atualizarGrid(perdedora.getLinha(), perdedora.getColuna(), '.');
        if(vencedora.getTipo() == "Barbara"){
            atualizarGrid(vencedora.getLinha(), vencedora.getColuna(), '!');
        }

        desativarAutoMover(perdedora.getId());
        caravanas.erase(std::remove_if(caravanas.begin(),
                                       caravanas.end(),
                                       [&perdedora](const std::unique_ptr<Caravana>& c)
                                       { return c.get() == &perdedora; }),caravanas.end());

        std::cout << "Venceu a caravana do tipo " << vencedora.getTipo() << std::endl;
    }
}


void Mapa::executarInstantes(int n) {
    if (n <= 0) {
        std::cout << "Erro: Número de instantes deve ser maior que 0.\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << "Instante " << (i + 1) << "/" << n << ":\n";
        processarItens();

        // Gera novos itens periodicamente
        if (i % instantesEntreNovosItens == 0) {
            gerarItensAleatorios();
        }

        processarMovimentosAutomaticos(); // Move as caravanas automáticas
        processarCombates();
    }
}


void Mapa::comprarMercadoria(int idCaravana, int quantidade) {
    auto caravana = std::find_if(caravanas.begin(), caravanas.end(), [idCaravana](const std::unique_ptr<Caravana>& c) {
        if(c->getId() == idCaravana && c->getTipo() == "Comercio"){
            return c->getId() == idCaravana;
        } else{
            return false;
        }

    });

    if (caravana != caravanas.end()) {
        // Verificar se está em uma cidade
        bool estaEmCidade = false;

        for (const auto& cidade : cidades) {
            if (cidade->getLinha() == (*caravana)->getLinha() && cidade->getColuna() == (*caravana)->getColuna()) {
                estaEmCidade = true;
                cidade->comprarMercadoria(idCaravana,quantidade);
                break;
            }
        }

        if (!estaEmCidade) {
            std::cout << "A caravana precisa estar em uma cidade para comprar mercadoria.\n";
            return;
        }

    } else {
        std::cout << "Caravana com ID " << idCaravana << " não é do tipo Comércio.\n";
    }
}

void Mapa::venderMercadoria(int idCaravana) {
    auto caravana = std::find_if(caravanas.begin(), caravanas.end(), [idCaravana](const std::unique_ptr<Caravana>& c) {
        if(c->getId() == idCaravana && c->getTipo() == "Comercio"){
            return c->getId() == idCaravana;
        } else{
            return false;
        }

    });

    if (caravana != caravanas.end()) {
        // Verificar se está em uma cidade
        bool estaEmCidade = false;

        for (const auto& cidade : cidades) {
            if (cidade->getLinha() == (*caravana)->getLinha() && cidade->getColuna() == (*caravana)->getColuna()) {
                estaEmCidade = true;
                cidade->venderMercadoria(idCaravana);
                break;
            }
        }

        if (!estaEmCidade) {
            std::cout << "A caravana precisa estar em uma cidade para vender mercadoria.\n";
            return;
        }
    } else {
        std::cout << "Caravana com ID " << idCaravana << " não é do tipo Comércio.\n";
    }
}

void Mapa::comprarCaravanaCidade(const std::string& nome, const std::string& tipo) {
    auto cidade = std::find_if(cidades.begin(), cidades.end(), [nome](const std::unique_ptr<Cidade>& c) {
        return c->getNome() == nome;
    });

    if (cidade != cidades.end()) {
        cidade->get()->comprarCaravana(tipo);
    } else {
        std::cout << "Cidade com o nome " << nome << " não encontrada.\n";
    }
}



int Mapa::getMoedas() const {
    return moedas;
}

int Mapa::getPrecoCaravana()  const {
    return precoCaravana; // Return the caravan price
}

void Mapa::criarTempestadeAreia(int linha, int coluna, int raio) {
    if (raio <= 0) {
        std::cout << "Erro: O raio deve ser maior que zero.\n";
        return;
    }

    // Determinar os limites da área afetada
    int inicioLinha = std::max(0, linha - raio);
    int fimLinha = std::min(linhas - 1, linha + raio);
    int inicioColuna = std::max(0, coluna - raio);
    int fimColuna = std::min(colunas - 1, coluna + raio);

    std::cout << "A criar tempestade de areia na area centrada em (" << linha << ", " << coluna << ") com raio " << raio << ".\n";

    // Iterar por todas as caravanas para verificar quais estão na área afetada
    for (auto it = caravanas.begin(); it != caravanas.end();) {
        auto& caravana = *it;
        int linhaCaravana = caravana->getLinha();
        int colunaCaravana = caravana->getColuna();

        // Verificar se a caravana está dentro da área afetada
        if (linhaCaravana >= inicioLinha && linhaCaravana <= fimLinha &&
            colunaCaravana >= inicioColuna && colunaCaravana <= fimColuna) {
            std::cout << "Caravana " << caravana->getId() << " foi atingida pela tempestade de areia.\n";

            // Aplicar efeitos dependendo do tipo da caravana
            if (caravana->getTipo() == "Comercio") {
                if (rand() % 100 < 50 && caravana->getCargaAtual() > caravana->getCapacidadeCarga() / 2) {
                    std::cout << "Caravana de Comercio " << caravana->getId() << " foi destruida.\n";
                    atualizarGrid(linhaCaravana, colunaCaravana, '.'); // Limpa a posição no grid
                    it = caravanas.erase(it); // Remove caravana destruída
                    continue;
                } else if (rand() % 100 < 25) {
                    std::cout << "Caravana de Comercio " << caravana->getId() << " foi destruida.\n";
                    atualizarGrid(linhaCaravana, colunaCaravana, '.'); // Limpa a posição no grid
                    it = caravanas.erase(it); // Remove caravana destruída
                    continue;
                } else {
                    std::cout << "Caravana de Comercio " << caravana->getId() << " perdeu 25% da carga.\n";
                    caravana->removerCarga(static_cast<int>(caravana->getCargaAtual() * 0.25));
                }
            } else if (caravana->getTipo() == "Militar") {
                std::cout << "Caravana Militar " << caravana->getId() << " perdeu 10% dos tripulantes.\n";
                caravana->removerTripulantes(static_cast<int>(caravana->getTripulantes() * 0.10));
                if (rand() % 100 < 33) {
                    std::cout << "Caravana Militar " << caravana->getId() << " foi destruida.\n";
                    atualizarGrid(linhaCaravana, colunaCaravana, '.'); // Limpa a posição no grid
                    it = caravanas.erase(it); // Remove caravana destruída
                    continue;
                }
            } else {
                std::cout << "Caravana " << caravana->getId() << " perdeu 10% dos tripulantes.\n";
                caravana->removerTripulantes(static_cast<int>(caravana->getTripulantes() * 0.10));
                if (rand() % 100 < 25) {
                    std::cout << "Caravana " << caravana->getId() << " foi destruída.\n";
                    atualizarGrid(linhaCaravana, colunaCaravana, '.'); // Limpa a posição no grid
                    it = caravanas.erase(it); // Remove caravana destruída
                    continue;
                }
            }
        }
        ++it; // Avança o iterador se a caravana não for destruída
    }

    std::cout << "Tempestade de areia processada.\n";
}


bool Mapa::estaAdjacente(int linha1, int coluna1, int linha2, int coluna2) const {
    return (linha1 == linha2 && std::abs(coluna1 - coluna2) == 1) || // Mesma linha, colunas adjacentes
           (coluna1 == coluna2 && std::abs(linha1 - linha2) == 1) ||   // Mesma coluna, linhas adjacentes
           (std::abs(linha1 - linha2) == 1 && std::abs(coluna1 - coluna2) == 1); // Diagonal adjacente
}

std::vector<std::pair<int, int>> Mapa::encontrarCaravanasAdjacentes(int linha, int coluna) const {
    std::vector<std::pair<int, int>> proximas;
    for (const auto& caravana : caravanas) {
        if (estaAdjacente(caravana->getLinha(), caravana->getColuna(), linha, coluna)) {
            proximas.emplace_back(caravana->getLinha(), caravana->getColuna());
        }
    }
    return proximas;
}







Item* Mapa::encontrarItemProximo(int linha, int coluna, int raio) const {
    for (auto& item : itens) {
        int distLinha = std::abs(item.linha - linha);
        int distColuna = std::abs(item.coluna - coluna);
        if (distLinha <= raio && distColuna <= raio) {
            return const_cast<Item*>(&item);
        }
    }
    return nullptr;
}













void Mapa::adicionarCaravanaBarbara(int linha, int coluna) {

    // Verificar se a posição está livre para adicionar uma caravana bárbara
    if (obterGrid(linha, coluna) == '.') {
        atualizarGrid(linha,coluna, '!');
        adicionarCaravana(std::make_unique<CaravanaBarbara>(gerarIDCaravana(), linha, coluna));

        std::cout << "Nova caravana bárbara gerada em (" << linha << ", " << coluna << ")." << std::endl;
    }
}

Caravana* Mapa::encontrarCaravanaBarbaraProxima(int linha, int coluna, int raio) const {
    for (const auto& caravana : caravanas) {
        int distLinha = std::abs(caravana->getLinha() - linha);
        int distColuna = std::abs(caravana->getColuna() - coluna);
        if (distLinha <= raio && distColuna <= raio && caravana->getTipo() == "Barbara") {
            return caravana.get();
        }
    }
    return nullptr;
}


void Mapa::atualizarBuffer() {
    buffer->limparBuffer();

    // Atualizar o buffer com o grid do mapa
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            buffer->moverCursor(i, j);
            buffer->escreverCaractere(obterGrid(i, j));
        }
    }

    // Adicionar informações adicionais no buffer
    buffer->moverCursor(linhas, 0);
    *buffer << "Moedas: " << moedas << "\n";
    *buffer << "Caravanas: " << caravanas.size() << "\n";
    /*
    *buffer << "Cidades: " << cidades.size() << "\n";
    */
    *buffer << "Itens: " << itens.size() << "\n";
}

void Mapa::removerItem(int linha, int coluna) {
    auto it = std::find_if(itens.begin(), itens.end(), [linha, coluna](const Item& item) {
        return item.linha == linha && item.coluna == coluna;
    });

    if (it != itens.end()) {
        itens.erase(it);
    }
}


void Mapa::contratarTripulantes(int idCaravana, int quantidade) {
    auto caravana = std::find_if(caravanas.begin(), caravanas.end(), [idCaravana](const std::unique_ptr<Caravana>& c) {
        return c->getId() == idCaravana;
    });

    if (caravana == caravanas.end()) {
        std::cout << "Erro: Caravana com ID " << idCaravana << " não encontrada.\n";
        return;
    }

    // Verificar se a caravana está em uma cidade
    bool estaEmCidade = false;
    for (const auto& cidade : cidades) {
        if ((*caravana)->getLinha() == cidade->getLinha() && (*caravana)->getColuna() == cidade->getColuna()) {
            estaEmCidade = true;
            break;
        }
    }

    if (!estaEmCidade) {
        std::cout << "Erro: Caravana " << idCaravana << " nao esta numa cidade.\n";
        return;
    }

    int custo = quantidade; // 1 moeda por tripulante
    if (moedas >= custo) {
        (*caravana)->adicionarTripulantes(quantidade);
        moedas -= custo;
        std::cout << "Caravana " << idCaravana << " contratou " << quantidade << " tripulantes por " << custo << " moedas.\n";
    } else {
        std::cout << "Erro: Moedas insuficientes para contratar tripulantes.\n";
    }
}





/*
void Mapa::executarSimulacao() {
    bool houveMudanca = false;

    // Movimentação automática das caravanas
    for (auto& caravana : caravanas) {
        auto posAnterior = std::make_pair(caravana->getLinha(), caravana->getColuna());
        caravana->executarComportamento(*this);
        auto posAtual = std::make_pair(caravana->getLinha(), caravana->getColuna());

        if (posAnterior != posAtual) {
            std::cout << "Caravana " << caravana->getId()
                      << " moveu-se de (" << posAnterior.first << ", " << posAnterior.second
                      << ") para (" << posAtual.first << ", " << posAtual.second << ")." << std::endl;
            houveMudanca = true;
        }
    }

    // Gerar novos itens, respeitando o limite de itens no mapa
    if (itens.size() < static_cast<size_t>(maxItens)) {
        adicionarItemAleatorio();
        houveMudanca = true;
    }

    // Gerar novas caravanas bárbaras, respeitando o intervalo configurado
    static int contadorBarbaros = 0;
    if (++contadorBarbaros >= instantesEntreNovosBarbaros) {
        adicionarCaravanaBarbaraAleatoria();
        contadorBarbaros = 0;
        houveMudanca = true;
    }

    // Atualizar o buffer apenas se houve mudanças
    if (houveMudanca) {
        atualizarBuffer();
        buffer->imprimirBuffer();
    }
}
*/

void Mapa::listagem_precos() const {
    std::cout << "Preço de Compra da Mercadoria: " << precoCompraMercadoria << std::endl;
    std::cout << "Preço de Venda da Mercadoria: " << precoVendaMercadoria << std::endl;
}


void Mapa::gerarItensAleatorios() {
    while (itens.size() < maxItens) {
        int linha = rand() % linhas;
        int coluna = rand() % colunas;

        // Verificar se a posição está vazia
        if (posicaoValida(linha, coluna) && grid[calcularIndice(linha, coluna)] == '.') {
            Item::Tipo tipo = static_cast<Item::Tipo>(rand() % 5); // Escolhe tipo aleatório
            itens.emplace_back(linha, coluna, tipo, 20);          // Configura duração de 20 instantes
            grid[calcularIndice(linha, coluna)] = 'I';           // Marca item no grid
            std::cout << "Novo item (" << itens.back().getNomeTipo()
                      << ") gerado em (" << linha << ", " << coluna << ").\n";
        }
    }
}


void Mapa::processarItens() {
    for (auto it = itens.begin(); it != itens.end();) {
        it->duracao--;

        // Remover itens com duração expirada
        if (it->duracao <= 0) {
            std::cout << "Item (" << it->getNomeTipo() << ") em (" << it->linha << ", "
                      << it->coluna << ") desapareceu.\n";
            grid[calcularIndice(it->linha, it->coluna)] = '.'; // Limpa o grid
            it = itens.erase(it);
        } else {
            ++it;
        }
    }
}

void Mapa::verificarItensAdjacentes(Caravana& caravana) {
    for (auto it = itens.begin(); it != itens.end();) {
        int distLinha = abs(it->linha - caravana.getLinha());
        int distColuna = abs(it->coluna - caravana.getColuna());

        if ((distLinha == 1 && distColuna == 0) || (distLinha == 0 && distColuna == 1)) {
            it->aplicarEfeito(caravana, *this);
            grid[calcularIndice(it->linha, it->coluna)] = '.'; // Limpa o grid
            it = itens.erase(it); // Remove o item
        } else {
            ++it;
        }
    }
}

