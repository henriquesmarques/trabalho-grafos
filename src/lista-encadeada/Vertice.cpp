#include "Vertice.h"
#include "Aresta.h"
#include <iostream>

using namespace std;

Vertice::Vertice(int _id) {
    id = _id;
    peso = 1;
    prox = NULL;
    aresta = NULL;
}

Vertice::~Vertice() {
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
