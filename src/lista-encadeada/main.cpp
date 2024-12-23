#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main() {

    GrafoLista g;
    g.carregaGrafo();

    if (g.arestaPonderada())
        cout << "Arestas ponderadas." << endl;
    else
        cout << "Arestas nao ponderadas." << endl;

    cout << "Ordem do grafo: " << g.getOrdem() << endl;

    if (g.ehDirecionado())
        cout << "Eh direcionado." << endl;
    else
        cout << "Nao eh direcionado." << endl;

    if (g.ehConexo())
        cout << "Eh conexo." << endl;
    else
        cout << "Nao eh conexo." << endl;

    return 0;
}