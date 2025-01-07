#include "GrafoLista.h"
#include "Vertice.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

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

    //imprimirVertices();

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
        fim->inserirAresta(a);

        // Adicionando aresta na lista
        if (raizAresta != nullptr) {
            a->setProx(raizAresta);
        }
        raizAresta = a;

        //cout << "Aresta inserida: " << a->getInicio()->getId() << " -> " << a->getFim()->getId() << endl;
    }
}

void GrafoLista::inserirPonteiroAresta(Aresta* a) {
    // Adicionando ponteiro da aresta no vértice
    a->getInicio()->inserirAresta(a);
    a->getFim()->inserirAresta(a);

    // Adicionando aresta na lista
    if (raizAresta != nullptr) {
        a->setProx(raizAresta);
    }
    raizAresta = a;
}

void GrafoLista::imprimirVertices() {
    cout << "Lista de vertices: " << endl;
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

int GrafoLista::sortearVertice(int n) {
    return rand() % n + 1;
}

int GrafoLista::sortearPeso(int n) {
    return rand() % (2 * n + 1) - n;
}

Aresta* GrafoLista::inserirArestaAleatoria(int ordem, int peso) {
    Aresta* a = new Aresta(buscaVertice(sortearVertice(ordem)),buscaVertice(sortearVertice(ordem)),peso);
    while (a->getInicio() == a->getFim()) {
        a->setInicio(buscaVertice(sortearVertice(ordem)));
        a->setFim(buscaVertice(sortearVertice(ordem)));
    }
    inserirPonteiroAresta(a);
    return a;
}

void GrafoLista::novo_grafo() {
    srand(time(0));
    ifstream arquivo;

    arquivo.open("C:/Users/henri/CLionProjects/trabalho-grafos/Descricao.txt", ios::in);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    int grau, ordem, componentesConexas;
    bool direcionado, verticesPonderados,arestasPonderadas, completo, bipartido, arvore, arestaPonte, verticeArticulacao;

    arquivo >> grau >> ordem >> direcionado >> componentesConexas >> verticesPonderados >> arestasPonderadas >> completo
            >> bipartido >> arvore >> arestaPonte >> verticeArticulacao;

    this->direcionado = direcionado;

    // Vertice de Articulação
    if (verticeArticulacao) {
        ordem--;
        componentesConexas++;
    }

    // Criando vértices
    if (verticesPonderados)
        for (int i = 0; i < ordem; i++)
            inserirVertice(i+1, sortearPeso(20));
    else
        for (int i = 0; i < ordem; i++)
            inserirVertice(i+1, 1);

    if (completo) {
        // bipartido = false
        // arvore = false
        // arestaPonte = false
        // verticeArticulacao = false
        // componenteConexa = 1
        // grau = ordem - 1
        if (direcionado) {
            for (int i = 1; i <= ordem; i++)
                for (int j = 1; j <= ordem; j++)
                    if (i != j) {
                        if (arestasPonderadas)
                            inserirAresta(buscaVertice(i), buscaVertice(j), sortearPeso(20));
                        else
                            inserirAresta(buscaVertice(i), buscaVertice(j), 1);
                    }
        }
        else {
            for (int i = 1; i <= ordem; i++)
                for (int j = 1; j <= ordem; j++)
                    if (i > j) {
                        if (arestasPonderadas)
                            inserirAresta(buscaVertice(i), buscaVertice(j), sortearPeso(20));
                        else
                            inserirAresta(buscaVertice(i), buscaVertice(j), 1);
                    }
        }
    } else {
        int compConexo = 0;
        int _grau = 0;
        //bool vertArticulacao = false;
        while (compConexo != componentesConexas && _grau != grau /*&& vertArticulacao != verticeArticulacao*/) {
            Aresta *a;
            if (arestasPonderadas)
                a = inserirArestaAleatoria(ordem, sortearPeso(20));
            else
                a = inserirArestaAleatoria(ordem, 1);
            compConexo = n_conexo();
            _grau = get_grau();
            //vertArticulacao = possui_articulacao();
            if (compConexo < componentesConexas || _grau > grau) {
                removerAresta(a);
            }
        }

        /*if (verticeArticulacao) {
            ordem++;
            componentesConexas--;

            if (vertice_ponderado())
                inserirVertice(ordem, sortearPeso(20));
            else
                inserirVertice(ordem, 1);

            while (compConexo != componentesConexas && _grau != grau && vertArticulacao != verticeArticulacao) {
                // Inserir aresta com origem Vértice[Ordem] e destino uma das componentes
                if (arestasPonderadas)
                    inserirAresta(buscaVertice(ordem), buscaVertice(sortearVertice(ordem-1)), sortearPeso(20));
                else
                    inserirAresta(buscaVertice(ordem), buscaVertice(sortearVertice(ordem-1)), 1);
                compConexo = n_conexo();
                _grau = get_grau();
                vertArticulacao = possui_articulacao();
                if (compConexo > componentesConexas || _grau > grau) {
                    removerAresta(raizAresta);
                }
            }
        }*/
    }

    imprimirVertices();
    imprimirArestas();

    cout << "Grau: " << get_grau() << endl << "Ordem: " << get_ordem() << endl << "Direcionado: " << eh_direcionado() << endl <<
        "Componentes conexas: " << n_conexo() << endl << "Vertices ponderados: " << vertice_ponderado() << endl <<
        "Arestas ponderadas: " << aresta_ponderada() << endl << "Completo: " << eh_completo() /*<< endl <<
        "Bipartido: " << ehBipartido()*/ << endl << "Arvore: " << eh_arvore() /*<< endl << "Aresta Ponte: " <<
        possuiPonte()*/ << endl << "Vertice de Articulacao: " << possui_articulacao() << endl;
}

// Grau
// Ordem*
// Direcionado*
// Vertices ponderados*
// Arestas ponderadas

// Completo*
// Componentes conexas
// Bipartido
// Arvore
// Aresta Ponte
// Vertice de Articulação


// Bipartido:
// Separar em dois grupos
// Sortear um de cada grupo para criar uma aresta

// Sortear uma aresta
// Insere
// Descumpriu alguma imposição?
// Se não, então continua
// Se sim, remove e sorteia novamente

// Grafo conexo
// adicionar arestas até o número de componentes ser igual a 1

// Aresta ponte
// N componentes conexas - 1
// criar dois grupos
// criar uma aresta que liga eles

// Vertice de articulação
// (adicionar um vertice no final)