//
// Created by henri on 20/12/2024.
//

#ifndef VERTICE_H
#define VERTICE_H
#include "Aresta.h"

class Vertice {
public:
    Vertice();
    ~Vertice();
    void setPeso(int val);
    int getPeso();
    void setProx(Vertice* v);
    Vertice* getProx();
    void setAresta(Aresta* a);
    Aresta* getAresta();
private:
    int peso;
    Vertice* prox;
    Aresta* aresta;
};

#endif //VERTICE_H
