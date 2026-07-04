#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static void addEdge(vector<string>& graph, int a, int b) {
    if (a == b) return;
    graph[a][b] = 'Y';
    graph[b][a] = 'Y';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 15);
    int mode = (n == 1) ? 0 : rnd.next(0, 6);
    vector<string> graph(n, string(n, 'N'));

    if (mode == 0) {
        // Empty graph, including the n = 1 corner case.
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                addEdge(graph, i, j);
    } else if (mode == 2) {
        for (int i = 0; i + 1 < n; ++i)
            addEdge(graph, i, i + 1);
    } else if (mode == 3) {
        int center = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i)
            addEdge(graph, center, i);
    } else if (mode == 4) {
        int groups = rnd.next(2, min(5, n));
        vector<int> group(n);
        for (int i = 0; i < n; ++i)
            group[i] = rnd.next(0, groups - 1);

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double p = (group[i] == group[j]) ? rnd.next(0.65, 0.95)
                                                   : rnd.next(0.00, 0.20);
                if (rnd.next() < p)
                    addEdge(graph, i, j);
            }
        }
    } else if (mode == 5) {
        vector<int> side(n);
        for (int i = 0; i < n; ++i)
            side[i] = rnd.next(0, 1);

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double p = (side[i] != side[j]) ? rnd.next(0.45, 0.85)
                                                 : rnd.next(0.00, 0.10);
                if (rnd.next() < p)
                    addEdge(graph, i, j);
            }
        }
    } else {
        double density = rnd.next(0.05, 0.85);
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (rnd.next() < density)
                    addEdge(graph, i, j);
    }

    println(n);
    for (const string& row : graph)
        println(row);

    return 0;
}
