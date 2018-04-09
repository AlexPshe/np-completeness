#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        cout << numVertices + edges.size() * 3 << ' ' << numVertices * 3 << endl;
        for (int i = 0; i < numVertices; i++){
            cout << i * 3 + 1 << ' ' << i * 3 + 2 << ' ' << i * 3 + 3 << " 0" << endl;
        }

        for (int i = 0; i < edges.size(); i++)
            for (int k = 1; k <= 3; k++)
                cout <<'-'<< (edges[i].from - 1) * 3 + k << " -"<< (edges[i].to - 1) * 3 + k << " 0" << endl;

    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}