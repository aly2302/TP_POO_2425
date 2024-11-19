#include "Mapa.h"
#include <fstream>
#include <iostream>
#include <cstring>

// Construtor
Mapa::Mapa(const std::string& fileName)
        : rows(0), cols(0), buffer(nullptr), grid(nullptr) {
    carregarMapa(fileName);
}

// Destrutor
Mapa::~Mapa() {
    delete buffer;
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

// Carregar mapa a partir de um arquivo
void Mapa::carregarMapa(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        throw std::runtime_error("Erro ao abrir o ficheiro: " + fileName);
    }

    file >> rows >> cols;
    file.ignore(); // Ignorar a linha nova

    grid = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new char[cols];
        std::memset(grid[i], '.', cols); // Preenche com '.'
    }

    // Inicializando o buffer com as dimensões
    buffer = new Buffer(rows, cols);

    // Lendo o mapa linha por linha
    for (int i = 0; i < rows; ++i) {
        std::string line;
        std::getline(file, line);
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = line[j]; // Atualiza o estado lógico
        }
    }
    atualizarBuffer();
}

// Atualizar o buffer com o estado atual do mapa
void Mapa::atualizarBuffer() {
    buffer->clear();  // Limpa o buffer
    for (int i = 0; i < rows; ++i) {
        buffer->moveCursor(i, 0);
        for (int j = 0; j < cols; ++j) {
            *buffer << grid[i][j];
        }
    }
}

// Mostrar o mapa no console
void Mapa::mostrarMapa() const {
    buffer->print();
}

// Mover uma caravana
void Mapa::moverCaravana(char id, int novaLinha, int novaColuna) {
    if (novaLinha < 0 || novaLinha >= rows || novaColuna < 0 || novaColuna >= cols) {
        throw std::out_of_range("Movimento fora do limite do mapa");
    }

    bool found = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == id) {
                grid[i][j] = '.'; // Limpar posição antiga
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        throw std::runtime_error("Caravana não encontrada no mapa");
    }

    if (grid[novaLinha][novaColuna] == '.') {
        grid[novaLinha][novaColuna] = id;
        atualizarBuffer();
    } else {
        throw std::runtime_error("Posição ocupada por outro elemento");
    }
}
