#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    ifstream arquivo;
    arquivo.open("C:/Users/henri/CLionProjects/trabalho-grafos/Grafo.txt", ios::in);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    int num_nos, direcionado, ponderado_nos, ponderado_arestas;
    arquivo >> num_nos >> direcionado >> ponderado_nos >> ponderado_arestas;

    // Vetor para armazenar os pesos dos nós
    if (ponderado_nos == 1) {
        int pesos_nos[num_nos];
        for (int i = 0; i < num_nos; ++i) {
            arquivo >> pesos_nos[i];
        }
    }

    // Vetor de pares para armazenar as arestas
    vector<pair<int, int> > arestas;
    vector<int> pesos_arestas;
    int origem, destino, peso;
    while (arquivo >> origem >> destino) {
        arestas.emplace_back(origem, destino);
        if (ponderado_arestas) {
            arquivo >> peso;
            pesos_arestas.push_back(peso);
        }
    }

    arquivo.close();

    // Agora você pode utilizar as variáveis num_nos, direcionado, ponderado_nos,
    // ponderado_arestas, pesos_nos, arestas e pesos_arestas para realizar
    // as operações desejadas no grafo

    // Exemplo: Imprimindo as arestas
    for (int i = 0; i < arestas.size(); ++i) {
        cout << "Aresta " << i + 1 << ": " << arestas[i].first << " -> " << arestas[i].second;
        if (ponderado_arestas) {
            cout << " (peso: " << pesos_arestas[i] << ")";
        }
        cout << endl;
    }

    return 0;
}

/// Grafo.txt
///3 1 1 1  // numero de nos, direcionado, ponderado vertices, ponderado arestas
///2 3 7    // peso dos nos (apenas se ponderado nos vertices)
///1 2 6    // origem, destino, peso (peso apenas se ponderado na aresta)
///2 1 4    // origem, destino, peso (peso apenas se ponderado na aresta)
///2 3 −5   // origem, destino, peso (peso apenas se ponderado na aresta)
