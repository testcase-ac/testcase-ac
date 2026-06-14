#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    inf.readInt(0, 150000, "H");
    inf.readEoln();

    vector<int> parent(n + 1);
    int root = 0;
    long long totalWeight = 0;

    for (int vertex = 1; vertex <= n; ++vertex) {
        parent[vertex] = inf.readInt(0, n, "parent");
        inf.readSpace();
        long long weight = inf.readLong(0LL, 1000000000LL, "weight");
        inf.readEoln();

        if (parent[vertex] == 0) {
            ensuref(weight == 0,
                    "root row for vertex %d must have weight 0, found %lld",
                    vertex, weight);
            ensuref(root == 0,
                    "multiple root rows: vertices %d and %d", root, vertex);
            root = vertex;
        } else {
            ensuref(parent[vertex] != vertex,
                    "vertex %d cannot be its own parent", vertex);
            totalWeight += weight;
            ensuref(totalWeight <= 1000000000LL,
                    "sum of edge weights exceeds 1000000000");
        }
    }

    ensuref(root != 0, "there must be exactly one root row");

    vector<int> state(n + 1, 0);
    for (int start = 1; start <= n; ++start) {
        int current = start;
        while (current != 0 && state[current] == 0) {
            state[current] = start;
            current = parent[current];
        }
        ensuref(current == 0 || state[current] != start,
                "cycle detected while tracing parent links from vertex %d",
                start);
    }

    inf.readEof();
    return 0;
}
