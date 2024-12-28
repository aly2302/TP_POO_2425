#include "Cidade.h"

// Método para comprar uma caravana
bool Cidade::comprarCaravana() {
    if (caravanasDisponiveis.empty()) {
        std::cout << "Não há caravanas disponíveis para compra." << std::endl;
        return false; // Retorna se não houver caravanas disponíveis
    }

    // Tenta comprar a primeira caravana disponível
    std::unique_ptr<Caravana> caravana = std::move(caravanasDisponiveis.front()); // Pega a primeira caravana

    if (mapa.getMoedas() >= mapa.getPrecoCaravana()) { // Preço da caravana
        // Deduzir o custo
        mapa.reduzirMoedas(mapa.getPrecoCaravana());
        std::cout << "Caravana comprada com sucesso!" << std::endl;

        // Mover o unique_ptr para o mapa
        mapa.adicionarCaravana(std::move(caravana));

        // Remove a caravana da lista
        caravanasDisponiveis.erase(caravanasDisponiveis.begin()); // Remove a caravana da lista
        return true; // Retorna que a compra foi bem-sucedida
    } else {
        std::cout << "Moedas insuficientes para comprar a caravana." << std::endl;
        return false; // Retorna que a compra falhou
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

void Cidade::comprarMercadoria(int idCaravana, int quantidade) const {
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
        int custoTotal = quantidade; // 1 moeda por tonelada
        if (mapa.getMoedas() >= custoTotal && !(*caravana)->estaCheia()) {
            (*caravana)->adicionarCarga(quantidade);
            mapa.reduzirMoedas(custoTotal);
            std::cout << "Caravana " << idCaravana << " comprou " << quantidade << " toneladas de mercadoria.\n";
        } else {
            std::cout << "Moedas insuficientes ou caravana cheia.\n";
        }
    } else {
        std::cout << "Caravana com ID " << idCaravana << " não encontrada.\n";
    }
}

void Cidade::venderMercadoria(int idCaravana) const {
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
        int valorVenda = quantidade * 2; // 2 moedas por tonelada
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
}