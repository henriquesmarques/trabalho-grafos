#ifndef GRAFO_H
#define GRAFO_H

#include "Vertice.h"
#include "Aresta.h"

// Os grafos não devem aceitar arestas múltiplas ou laços
// Uso de lista encadeada tanto para vertices quanto arestas usando alocação dinâmica
// Aresta armazena 1 quando não é ponderada

class Grafo {
public:
    Grafo();
    ~Grafo();
    void setPrimeiro(Vertice* v);
    Vertice* getPrimeiro();

    void carregaGrafo();
    void inserirVertice(int id, int peso);
    void inserirAresta(Vertice* inicio, Vertice* fim, int peso);
    void imprimirVertices();
    void imprimirArestas();

    /// Carrega_grafo       função que lê um arquivo txt com um grafo e carrega ele
    /// Eh_conexo*          função que diz se o grafo é conexo
    /// N_conexo            função que indica a quantidade de componentes conexas
    /// Eh_arvore           função que diz se o grafo é uma árvore
    /// Get_ordem           função que retorna a ordem do grafo
    /// Eh_direcionado      função que retorna se o grafo é direcionado ou não
    /// Aresta_ponderada    função que informa se as arestas do grafo tem peso
private:
    Vertice* primeiroVertice;
    Aresta* primeiraAresta;
};

#endif //GRAFO_H
