//
// Created by henri on 20/12/2024.
//

#ifndef GRAFO_H
#define GRAFO_H
#include "Vertice.h"

// Os grafos não devem aceitar arestas múltiplas ou laços
// Uso de lista encadeada tanto para vertices quanto arestas usando alocação dinâmica
// Aresta armazena 1 quando não é ponderada

class Grafo {
public:
    Grafo();
    ~Grafo();
    void setPrimeiro(Vertice* v);
    Vertice* getPrimeiro();

    /// Carrega_grafo       função que lê um arquivo txt com um grafo e carrega ele
    /// Eh_conexo*          função que diz se o grafo é conexo
    /// N_conexo            função que indica a quantidade de componentes conexas
    /// Eh_arvore           função que diz se o grafo é uma árvore
    /// Get_ordem           função que retorna a ordem do grafo
    /// Eh_direcionado      função que retorna se o grafo é direcionado ou não
    /// Aresta_ponderada    função que informa se as arestas do grafo tem peso
private:
    Vertice* primeiro;
};

#endif //GRAFO_H
