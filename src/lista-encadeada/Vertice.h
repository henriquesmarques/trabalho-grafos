#ifndef VERTICE_H
#define VERTICE_H
#include "Aresta.h"

class Aresta;

class Vertice {
public:
    Vertice(int _id);
    ~Vertice();
    void setPeso(int val);
    int getPeso();
    void setProx(Vertice* v);
    Vertice* getProx();
    int getId();
    void setArestas(Aresta* a);
    Aresta* getArestas();
private:
    int id;
    int peso;
    Vertice* prox;
    Aresta* arestas;
};

#endif //VERTICE_H
