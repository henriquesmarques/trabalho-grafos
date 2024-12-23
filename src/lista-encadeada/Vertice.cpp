#include "Vertice.h"
#include <iostream>

using namespace std;

Vertice::Vertice(int _id) {
    id = _id;
    peso = 1;
    prox = nullptr;
    arestas = nullptr;
}

Vertice::~Vertice() {
    delete [] arestas;
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

int Vertice::getId() {
    return id;
}

void Vertice::setArestas(Aresta *a) {
    arestas = a;
}

Aresta * Vertice::getArestas() {
    return arestas;
}
