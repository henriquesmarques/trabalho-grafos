//
// Created by henri on 20/12/2024.
//

#include "Vertice.h"
#include <iostream>

Vertice::Vertice(int _id) {
    id = _id;
    peso = 1;
    prox = NULL;
    aresta = NULL;
}

Vertice::~Vertice() {
    while (aresta != NULL) {
        Aresta* p = aresta->getProx();
        delete aresta;
        aresta = p;
    }
}

void Vertice::setPeso(int val) {
    peso = val;
}

int Vertice::getPeso() {
    return peso;
}

void Vertice::setProx(Vertice *v) {
    prox = v;
}

Vertice * Vertice::getProx() {
    return prox;
}

void Vertice::setAresta(Aresta *a) {
    aresta = a;
}

Aresta * Vertice::getAresta() {
    return aresta;
}

int Vertice::getId() {
    return id;
}
