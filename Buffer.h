#ifndef TP_POO_2425_BUFFER_H
#define TP_POO_2425_BUFFER_H

#include <string>

class Buffer {
private:
    char* buffer;
    int linhas;
    int colunas;
    int cursorLinha;
    int cursorColuna;

public:
    // Construtor para inicializar o buffer com dimensões definidas em tempo de execução
    Buffer(int linhas, int colunas);

    // Destrutor para libertar a memória
    ~Buffer();

    // Método para esvaziar o buffer (preencher com espaços)
    void esvaziarBuffer();

    // Método para mover o cursor para uma linha e coluna específicas
    void moverCursor(int linha, int coluna);

    // Método para imprimir um caractere no cursor atual
    void imprimirChar(char c);

    // Método para imprimir uma string no cursor atual
    void imprimirString(const std::string& str);

    // Método para imprimir um inteiro no cursor atual
    void imprimirInt(int valor);

    // Método para transcrever o conteúdo do buffer para a consola
    void transcreverParaConsola() const;
};


#endif //TP_POO_2425_BUFFER_H
