//
// Created by henri on 20/12/2024.
//

#ifndef GRAFO_H
#define GRAFO_H
#include "Vertice.h"

class Grafo {
public:
    Grafo();
    ~Grafo();
    void setPrimeiro(Vertice* v);
    Vertice* getPrimeiro();
private:
    Vertice* primeiro;
};

#endif //GRAFO_H
