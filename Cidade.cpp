#include "Cidade.h"

// Método para comprar uma caravana
bool Cidade::comprarCaravana(char tipo) {
    std::string tipoCaravana;

    // Traduzir o caractere para o tipo correspondente
    switch (tipo) {
        case 'C':
            tipoCaravana = "Comercio";
            break;
        case 'M':
            tipoCaravana = "Militar";
            break;
        case 'S':
            tipoCaravana = "Secreta";
            break;
        default:
            std::cout << "Tipo de caravana inválido. Use C, M ou S." << std::endl;
            return false;
    }

    // Procurar no vetor uma caravana do tipo especificado
    auto it = std::find_if(caravanasDisponiveis.begin(), caravanasDisponiveis.end(),
                           [&tipoCaravana](const std::unique_ptr<Caravana>& caravana) {
                               return caravana->getTipo() == tipoCaravana;
                           });

    if (it == caravanasDisponiveis.end()) {
        std::cout << "Não há caravanas do tipo " << tipoCaravana << " disponíveis para compra." << std::endl;
        return false; // Nenhuma caravana do tipo encontrado
    }

    // Verificar se há moedas suficientes para comprar a caravana
    if (mapa.getMoedas() >= mapa.getPrecoCaravana()) {
        // Deduzir o custo
        mapa.reduzirMoedas(mapa.getPrecoCaravana());

        // Mover o unique_ptr da caravana comprada para o mapa
        mapa.adicionarCaravana(std::move(*it));

        // Remover a caravana do vetor
        caravanasDisponiveis.erase(it);

        std::cout << "Caravana do tipo " << tipoCaravana << " comprada com sucesso!" << std::endl;
        return true;
    } else {
        std::cout << "Moedas insuficientes para comprar a caravana do tipo " << tipoCaravana << "." << std::endl;
        return false;
    }
}


void Cidade::comprarTripulantes(int idCaravana, int quantidade) const {
    // Encontrar a caravana pelo ID
    auto caravana = std::find_if(mapa.getCaravanas().begin(), mapa.getCaravanas().end(),
                                 [idCaravana](const std::unique_ptr<Caravana>& c) {
                                     return c->getId() == idCaravana;
                                 });

    if (caravana == mapa.getCaravanas().end()) {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada." << std::endl;
        return;
    }

    // Verificar se a caravana está na mesma posição que esta cidade
    if ((*caravana)->getLinha() == linha && (*caravana)->getColuna() == coluna) {
        // Calcular o custo total
        int custoTotal = quantidade; // 1 moeda por tripulante

        if (mapa.getMoedas() >= custoTotal) {
            // Adicionar tripulantes e deduzir moedas
            (*caravana)->adicionarTripulantes(quantidade);
            mapa.reduzirMoedas(custoTotal);

            std::cout << "Caravana " << idCaravana << " contratou " << quantidade
                      << " tripulantes por " << custoTotal << " moedas." << std::endl;
        } else {
            std::cout << "Moedas insuficientes para contratar " << quantidade
                      << " tripulantes." << std::endl;
        }
    } else {
        std::cout << "Caravana " << idCaravana
                  << " não está nesta cidade para contratar tripulantes." << std::endl;
    }
}

void Cidade::comprarMercadoria(int idCaravana, int quantidade, int preco_compra) const {
    // Encontrar a caravana pelo ID
    auto caravana = std::find_if(mapa.getCaravanas().begin(), mapa.getCaravanas().end(),
                                 [idCaravana](const std::unique_ptr<Caravana>& c) {
                                     return c->getId() == idCaravana;
                                 });

    if (caravana == mapa.getCaravanas().end()) {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada." << std::endl;
        return;
    }


    // Verificar se a caravana está na mesma posição que esta cidade
    if ((*caravana)->getLinha() == linha && (*caravana)->getColuna() == coluna) {
        int custoTotal = quantidade * preco_compra;
        if (mapa.getMoedas() >= custoTotal && !(*caravana)->estaCheia()) {
            (*caravana)->adicionarCarga(quantidade);
            mapa.reduzirMoedas(custoTotal);
            std::cout << "Caravana " << idCaravana << " comprou " << quantidade << " toneladas de mercadoria.\n" << " por: " << custoTotal << " moedas.\n";
        } else {
            std::cout << "Moedas insuficientes ou caravana cheia.\n";
        }
    } else {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada.\n";
    }
}

void Cidade::venderMercadoria(int idCaravana, int preco_venda) const {
    // Encontrar a caravana pelo ID
    auto caravana = std::find_if(mapa.getCaravanas().begin(), mapa.getCaravanas().end(),
                                 [idCaravana](const std::unique_ptr<Caravana>& c) {
                                     return c->getId() == idCaravana;
                                 });

    if (caravana == mapa.getCaravanas().end()) {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada." << std::endl;
        return;
    }


    // Verificar se a caravana está na mesma posição que esta cidade
    if ((*caravana)->getLinha() == linha && (*caravana)->getColuna() == coluna) {
        int quantidade = (*caravana)->getCargaAtual();
        int valorVenda = quantidade * preco_venda;
        mapa.addMoedas(valorVenda);
        (*caravana)->removerCarga(quantidade);

        std::cout << "Caravana " << idCaravana << " vendeu " << quantidade << " toneladas de mercadoria por " << valorVenda << " moedas.\n";

    } else {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada.\n";
    }
}


// Método para imprimir detalhes da cidade
void Cidade::imprimirDetalhes() const {
    std::cout << "Cidade: " << nome << " em (" << linha << ", " << coluna << ")" << std::endl;
    std::cout << "Número de caravanas disponíveis para comprar: " << caravanasDisponiveis.size() << std::endl;
}

// Método para imprimir detalhes da cidade
void Cidade::imprimirPrecos() const {
    std::cout << "Preço de Compra da Mercadoria: " << preco_compra << std::endl;
    std::cout << "Preço de Venda da Mercadoria: " << preco_venda << std::endl;
}