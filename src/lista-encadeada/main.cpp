#include <iostream>
#include "GrafoLista.h"

using namespace std;

void testarEhCiclico() {
    GrafoLista grafo;

    // Teste 1: Grafo sem ciclo
    grafo.inserirVertice(1, 1);
    grafo.inserirVertice(2, 1);
    grafo.inserirVertice(3, 1);
    grafo.inserirAresta(grafo.buscaVertice(1), grafo.buscaVertice(2), 1);
    grafo.inserirAresta(grafo.buscaVertice(2), grafo.buscaVertice(3), 1);
    std::cout << "Teste 1 (sem ciclo): " << (grafo.ehCiclico() ? "Falhou" : "Passou") << std::endl;

    // Teste 2: Grafo com ciclo
    grafo.inserirAresta(grafo.buscaVertice(3), grafo.buscaVertice(1), 1);
    std::cout << "Teste 2 (com ciclo): " << (grafo.ehCiclico() ? "Passou" : "Falhou") << std::endl;

    // Teste 3: Grafo direcionado sem ciclo
    GrafoLista grafoDirecionado;
    grafoDirecionado.inserirVertice(1, 1);
    grafoDirecionado.inserirVertice(2, 1);
    grafoDirecionado.inserirVertice(3, 1);
    grafoDirecionado.inserirAresta(grafoDirecionado.buscaVertice(1), grafoDirecionado.buscaVertice(2), 1);
    grafoDirecionado.inserirAresta(grafoDirecionado.buscaVertice(2), grafoDirecionado.buscaVertice(3), 1);
    grafoDirecionado.direcionado = true;
    std::cout << "Teste 3 (direcionado sem ciclo): " << (grafoDirecionado.ehCiclico() ? "Falhou" : "Passou") << std::endl;

    // Teste 4: Grafo direcionado com ciclo
    grafoDirecionado.inserirAresta(grafoDirecionado.buscaVertice(3), grafoDirecionado.buscaVertice(1), 1);
    std::cout << "Teste 4 (direcionado com ciclo): " << (grafoDirecionado.ehCiclico() ? "Passou" : "Falhou") << std::endl;
}

int main() {

    GrafoLista g;
    //g.carrega_grafo();
    g.novo_grafo();

    //testarEhCiclico();

    //cout << endl << endl;

    /*if (g.aresta_ponderada())
        cout << "Arestas ponderadas." << endl;
    else
        cout << "Arestas nao ponderadas." << endl;

    cout << "Ordem do grafo: " << g.get_ordem() << endl;

    if (g.eh_direcionado())
        cout << "Eh direcionado." << endl;
    else
        cout << "Nao eh direcionado." << endl;

    cout << "Eh " << g.n_conexo() << "-conexo." << endl;

    if (g.eh_arvore())
        cout << "Eh arvore." << endl;
    else
        cout << "Nao eh arvore." << endl;


    cout << endl << endl;

    if (g.verticePonderado())
        cout<< "Vertice Ponderada." << endl;
    else
        cout << "Nao eh vertice ponderada." << endl;

    cout<<"Grau do grafo: " << g.getGrau()<<endl;*/

    /*if (g.ehCompleto())
        cout << "Eh completo." << endl;
    else
        cout << "Nao eh completo." << endl;

    if (g.ehBipartido())
        cout << "Eh Bipartido." << endl;
    else
        cout << "Nao eh Bipartido." << endl;*/

    /*if (g.possuiArticulacao())
        cout << "Possui articulacao." << endl;
    else
        cout << "Nao possui articulacao." << endl;

    if (g.possuiPonte())
        cout<< "Possui Ponte." << endl;
    else
        cout << "Nao possui Ponte." << endl;*/

    return 0;
}
