#include "Grafo.h"
#include <iostream>
#include <fstream>

using namespace std;

Grafo::Grafo() {
    primeiroVertice = NULL;
    primeiraAresta = NULL;
}

Grafo::~Grafo() {
    while (primeiroVertice != NULL) {
        Vertice* p = primeiroVertice->getProx();
        delete primeiroVertice;
        primeiroVertice = p;
    }

    while (primeiraAresta != NULL) {
        Aresta* a = primeiraAresta->getProx();
        delete primeiraAresta;
        primeiraAresta = a;
    }
}

void Grafo::setPrimeiro(Vertice *v) {
    primeiroVertice = v;
}

Vertice * Grafo::getPrimeiro() {
    return primeiroVertice;
}

void Grafo::carregaGrafo() {
    ifstream arquivo;
    arquivo.open("C:/Users/henri/CLionProjects/trabalho-grafos/Grafo.txt", ios::in);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    int numVertices, direcionado, ponderado_nos, ponderado_arestas;
    arquivo >> numVertices >> direcionado >> ponderado_nos >> ponderado_arestas;

    // Criar vértices
    if (ponderado_nos == 1) {
        int peso;
        for (int i = 0; i < numVertices; ++i) {
            arquivo >> peso;
            inserirVertice(i+1, peso);
        }
    } else {
        for (int i = 0; i < numVertices; ++i) {
            inserirVertice(i+1, 1);
        }
    }

    imprimirVertices();

    // Criar arestas
    int origem, destino, peso;
    while (arquivo >> origem >> destino) {
        Vertice *v = primeiroVertice;
        Vertice *inicio = NULL;
        Vertice *fim = NULL;
        while (v != NULL) {
            if (v->getId() == origem) {
                inicio = v;
            }
            if (v->getId() == destino) {
                fim = v;
            }
            v = v->getProx();
        }

        if (inicio != NULL && fim != NULL) {
            if (ponderado_arestas == 1) {
                arquivo >> peso;
                inserirAresta(inicio, fim, peso);
            } else {
                inserirAresta(inicio, fim, 1);
            }
        } else {
            cout << "Erro ao inserir arquivo" << endl;
        }
    }

    imprimirArestas();
    arquivo.close();
}

void Grafo::inserirVertice(int id, int peso) {
    Vertice* v = new Vertice(id);
    v->setPeso(peso);
    if (primeiroVertice != NULL) {
        v->setProx(primeiroVertice);
    }
    primeiroVertice = v;
}

void Grafo::inserirAresta(Vertice *inicio, Vertice *fim, int peso) {
    Aresta* a = new Aresta();
    a->setPeso(peso);
    a->setInicio(inicio);
    a->setFim(fim);
    if (primeiraAresta != NULL) {
        a->setProx(primeiraAresta);
    }
    primeiraAresta = a;
}

void Grafo::imprimirVertices() {
    cout << "Lista de vertices: ";
    Vertice* v = primeiroVertice;
    while (v != NULL) {
        cout << v->getId() << " ";
        v = v->getProx();
    }
    cout << endl;
}

void Grafo::imprimirArestas() {
    cout << "Lista de arestas: " << endl;
    Aresta* a = primeiraAresta;
    while (a != NULL) {
        cout << a->getInicio()->getId() << " -> " << a->getFim()->getId() << " Peso: " << a->getPeso() << endl;
        a = a->getProx();
    }
}
