#include "GrafoLista.h"
#include "Vertice.h"
#include <iostream>
#include <fstream>

using namespace std;

GrafoLista::GrafoLista() {
    raizVertice = nullptr;
    raizAresta = nullptr;
    direcionado = false;
    // ordem = 0;
    // vertice_ponderado = false;
    // aresta_ponderada = false;
}

GrafoLista::~GrafoLista() {
    while (raizVertice != nullptr) {
        Vertice* p = raizVertice->getProx();
        delete raizVertice;
        raizVertice = p;
    }

    while (raizAresta != nullptr) {
        Aresta* a = raizAresta->getProx();
        delete raizAresta;
        raizAresta = a;
    }
}

void GrafoLista::carrega_grafo() {
    ifstream arquivo;
    arquivo.open("C:/Users/henri/CLionProjects/trabalho-grafos/Grafo.txt", ios::in);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    int numVertices, direcionado, ponderado_nos, ponderado_arestas;
    arquivo >> numVertices >> direcionado >> ponderado_nos >> ponderado_arestas;

    this->direcionado = direcionado;

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
        Vertice *v = raizVertice;
        Vertice *inicio = nullptr;
        Vertice *fim = nullptr;
        while (v != nullptr) {
            if (v->getId() == origem) {
                inicio = v;
            }
            if (v->getId() == destino) {
                fim = v;
            }
            v = v->getProx();
        }

        if (inicio != nullptr && fim != nullptr) {
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

    //imprimirArestas();
    arquivo.close();
}

void GrafoLista::inserirVertice(int id, int peso) {
    Vertice* v = new Vertice(id);
    v->setPeso(peso);
    if (raizVertice != nullptr) {
        v->setProx(raizVertice);
    }
    raizVertice = v;
}

void GrafoLista::inserirAresta(Vertice *inicio, Vertice *fim, int peso) {
    if (inicio == fim) {
        cout << "Erro: o grafo não permite inserir laço." << endl;
    } else {
        // Criando aresta
        Aresta* a = new Aresta();
        a->setPeso(peso);
        a->setInicio(inicio);
        a->setFim(fim);

        // Adicionando ponteiro da aresta no vértice
        inicio->inserirAresta(a);
        //if (!ehDirecionado()) {
            fim->inserirAresta(a);
        //}

        // Adicionando aresta na lista
        if (raizAresta != nullptr) {
            a->setProx(raizAresta);
        }
        raizAresta = a;

        cout << "Aresta inserida: " << a->getInicio()->getId() << " -> " << a->getFim()->getId() << endl;
    }
}

void GrafoLista::imprimirVertices() {
    cout << "Lista de vertices: ";
    Vertice* v = raizVertice;
    while (v != nullptr) {
        cout << v->getId() << " ";
        v = v->getProx();
    }
    cout << endl;
}

void GrafoLista::imprimirArestas() {
    cout << "Lista de arestas: " << endl;
    Aresta* a = raizAresta;
    while (a != nullptr) {
        cout << a->getInicio()->getId() << " -> " << a->getFim()->getId() << " Peso: " << a->getPeso() << endl;
        a = a->getProx();
    }
}

bool GrafoLista::aresta_ponderada() {
    Aresta *a = raizAresta;
    while (a != nullptr) {
        if (a->getPeso() != 1) {
            return true;
        }
        a = a->getProx();
    }
    return false;
}

int GrafoLista::get_ordem() {
    Vertice* v = raizVertice;
    int ordem = 0;
    while (v != nullptr) {
        ordem++;
        v = v->getProx();
    }
    return ordem;
}

bool GrafoLista::eh_direcionado() {
    return direcionado;
}

int GrafoLista::n_conexo() {
    int numVertices = get_ordem();
    if (numVertices == 0) return 0;

    bool *visitados = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visitados[i] = false;
    }

    int componentesConexas = 0;
    for (Vertice* v = raizVertice; v != nullptr; v = v->getProx()) {
        if (!visitados[v->getId() - 1]) {
            auxNConexo(visitados, v);
            componentesConexas++;
        }
    }

    delete[] visitados;
    return componentesConexas;
}

void GrafoLista::auxNConexo(bool *visitados, Vertice *v) {
    visitados[v->getId() - 1] = true;
    for (int i = 0; i < v->totalArestas(); ++i) {
        Aresta* a = v->getAresta(i);
        Vertice* adj = a->getFim();
        if (!visitados[adj->getId() - 1]) {
            auxNConexo(visitados, adj);
        }
        adj = a->getInicio();
        if (!visitados[adj->getId() - 1]) {
            auxNConexo(visitados, adj);
        }
    }
}

bool GrafoLista::ehCiclico() {
    int numVertices = get_ordem();
    if (numVertices == 0) return false;

    bool* visitados = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visitados[i] = false;
    }

    for (Vertice* v = raizVertice; v != nullptr; v = v->getProx()) {
        if (!visitados[v->getId() - 1]) {
            if (auxEhCiclico(v, visitados, nullptr)) {
                delete[] visitados;
                return true;
            }
        }
    }

    delete[] visitados;
    return false;
}

bool GrafoLista::auxEhCiclico(Vertice* v, bool* visitados, Vertice* pai) {
    visitados[v->getId() - 1] = true;

    for (int i = 0; i < v->totalArestas(); ++i) {
        Aresta* a = v->getAresta(i);
        Vertice* adj = a->getFim();

        if (!visitados[adj->getId() - 1]) {
            if (auxEhCiclico(adj, visitados, v)) {
                return true;
            }
        } else if (adj != pai) {
            return true;
        }
    }
    return false;
}

bool GrafoLista::eh_arvore() {
    if (n_conexo() == 1) {
        if (!ehCiclico())
            return true;
    }
    return false;
}

void GrafoLista::novo_grafo() {
}
