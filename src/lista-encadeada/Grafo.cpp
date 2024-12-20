//
// Created by henri on 20/12/2024.
//

#include "Grafo.h"
#include <iostream>

Grafo::Grafo() {
    primeiro = NULL;
}

Grafo::~Grafo() {
    while (primeiro != NULL) {
        Vertice* p = primeiro->getProx();
        delete primeiro;
        primeiro = p;
    }
}

void Grafo::setPrimeiro(Vertice *v) {
    primeiro = v;
}

Vertice * Grafo::getPrimeiro() {
    return primeiro;
}
