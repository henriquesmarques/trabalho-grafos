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
private:
    Vertice* raizVertice;
    Aresta* raizAresta;
    bool direcionado;
    void removerAresta(Aresta* a);
    void inserirVertice(int id, int peso);
    void inserirAresta(Vertice* inicio, Vertice* fim, int peso);
    void imprimirVertices();
    void imprimirArestas();
    bool ehConexo();
    bool ehCiclico();
    void auxEhConexo(bool *visitados, Vertice *v);
    bool auxEhCiclico(Vertice* v, bool* visitados, Vertice* pai);
    void auxNConexo(bool *visitados, Vertice *v);
};

#endif //GRAFO_H
