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
    void setRaizVertice(Vertice* v);
    Vertice* getRaizVertice();
    void setRaizAresta(Aresta* a);
    Aresta* getRaizAresta();

    void carregaGrafo(); /// Função que lê um arquivo txt com um grafo e carrega ele
    void inserirVertice(int id, int peso);
    void inserirAresta(Vertice* inicio, Vertice* fim, int peso);
    void imprimirVertices();
    void imprimirArestas();
    bool arestaPonderada(); /// Função que informa se as arestas do grafo tem peso
    int getOrdem(); /// Função que retorna a ordem do grafo
    bool ehConexo(); /// Função que diz se o grafo é conexo
    bool ehDirecionado(); /// Função que retorna se o grafo é direcionado ou não

    /// Eh_arvore           função que diz se o grafo é uma árvore
    /// N_conexo            função que indica a quantidade de componentes conexas
private:
    Vertice* raizVertice;
    Aresta* raizAresta;
    bool direcionado;
};

#endif //GRAFO_H
