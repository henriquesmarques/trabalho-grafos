#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main() {

    GrafoLista g;
    g.carrega_grafo();
    //g.novo_grafo();

    if (g.aresta_ponderada())
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

    cout << endl;

    if (g.vertice_ponderado())
        cout<< "Vertice Ponderada." << endl;
    else
        cout << "Nao eh vertice ponderada." << endl;

    cout<<"Grau do grafo: " << g.get_grau()<<endl;

    if (g.eh_completo())
        cout << "Eh completo." << endl;
    else
        cout << "Nao eh completo." << endl;

    if (g.eh_bipartido())
        cout << "Eh Bipartido." << endl;
    else
        cout << "Nao eh Bipartido." << endl;

    if (g.possui_articulacao())
        cout << "Possui articulacao." << endl;
    else
        cout << "Nao possui articulacao." << endl;

    if (g.possui_ponte())
        cout<< "Possui Ponte." << endl;
    else
        cout << "Nao possui Ponte." << endl;

    return 0;
}
