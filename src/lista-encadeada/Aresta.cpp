//
// Created by henri on 20/12/2024.
//

#include "Aresta.h"
#include <cstdio>

using namespace std;

Aresta::Aresta() {
    peso = 1;
    fim = inicio = NULL;
    prox = NULL;
}

Aresta::~Aresta() {
}

void Aresta::setPeso(int val) {
    peso = val;
}

int Aresta::getPeso() {
    return peso;
}

void Aresta::setInicio(Vertice *v) {
    inicio = v;
}

Vertice * Aresta::getInicio() {
    return inicio;
}

void Aresta::setFim(Vertice *v) {
    fim = v;
}

Vertice * Aresta::getFim() {
    return fim;
}

void Aresta::setProx(Aresta *a) {
    prox = a;
}

Aresta* Aresta::getProx() {
    return prox;
}
