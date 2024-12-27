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


// Método para imprimir detalhes da cidade
void Cidade::imprimirDetalhes() const {
    std::cout << "Cidade: " << nome << " em (" << linha << ", " << coluna << ")" << std::endl;
}