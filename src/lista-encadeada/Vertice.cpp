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

Aresta* Vertice::getAresta(int i) {
    if (i >= 0 && i < n) {
        return arestas[i];
    }
    else {
        cout << "Erro get: indice invalido." << endl;
        exit(1);
    }
}

void Vertice::inserirAresta(Aresta *a) {
    if (n >= tam) {
        aumentarVetor();
    }
    arestas[n] = a;
    n++;
}

void Vertice::aumentarVetor() {
    Aresta **a = new Aresta*[tam+10];
    for (int i = 0; i < tam; i++) {
        a[i] = arestas[i];
    }
    delete [] arestas;
    arestas = a;
    tam += 10;
}

int Vertice::totalArestas() {
    return n;
}
