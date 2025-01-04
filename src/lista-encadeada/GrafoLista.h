#ifndef GRAFO_H
#define GRAFO_H

#include "Vertice.h"
#include "Aresta.h"

// Os grafos não devem aceitar arestas múltiplas ou laços
// Uso de lista encadeada tanto para vertices quanto arestas usando alocação dinâmica
// Aresta armazena 1 quando não é ponderada

class Vertice;

class GrafoLista {
public:
    GrafoLista();
    ~GrafoLista();
    void carregaGrafo(); /// Função que lê um arquivo txt com um grafo e carrega ele
    bool arestaPonderada(); /// Função que informa se as arestas do grafo tem peso
    int getOrdem(); /// Função que retorna a ordem do grafo
    bool ehDirecionado(); /// Função que retorna se o grafo é direcionado ou não
    bool ehArvore(); /// Função que diz se o grafo é uma árvore
    int nConexo(); /// Função que indica a quantidade de componentes conexas
    bool ehConexo(); // !!!Funciona apenas para grafos direcionados!!!

    bool ehCompleto();  /// Função que diz se o grafo é completo ou não
    int getGrau();  /// Função que retorna o grau do grafo
    bool ehBipartido(); /// Função que diz se o grafo é bipartido ou não
    bool possuiArticulacao();   /// Função que diz se possui vertice de articulação
    bool possuiPonte(); /// Função que diz se possui aresta ponte
    bool verticePonderado();    /// Função que diz se o no possui peso
    void novo_grafo(); /// Função que lê um arquivo txt de configuração e gera um grafo aleatório

private:
    Vertice* raizVertice;
    Aresta* raizAresta;
    bool direcionado;
    void inserirVertice(int id, int peso);
    void inserirAresta(Vertice* inicio, Vertice* fim, int peso);
    void imprimirVertices();
    void imprimirArestas();
    void auxEhConexo(bool *visitados, Vertice *v);
    bool ehCiclico();
    bool auxEhCiclico(Vertice* v, bool* visitados, Vertice* pai);
    void auxNConexo(bool *visitados, Vertice *v);

    bool auxEhBipartido(int i, int c, int *cor);
    bool auxPonte(Vertice *v, int comp);
    bool auxArticulacao(Vertice *v, int comp);
    GrafoLista* copiarGrafo();
    void retiraVertice(int id);
    Aresta* buscaAresta(int id, int peso);
    Vertice* buscaVertice(int id);
    void removerAresta(Aresta* aresta);
};

#endif //GRAFO_H
