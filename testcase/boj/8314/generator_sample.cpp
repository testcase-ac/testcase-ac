#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    set<pair<int, int>> edgeSet;

    auto addEdge = [&](int a, int b) {
        if (a != b) edgeSet.emplace(a, b);
    };

    if (mode == 0) {
        // DAG with shuffled labels.
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());

        double density = rnd.next(0.15, 0.75);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < density) addEdge(p[i], p[j]);
            }
        }
    } else if (mode == 1) {
        // One directed cycle plus extra forward edges from a random order.
        int cycleLen = rnd.next(2, min(n, 8));
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());

        for (int i = 0; i < cycleLen; ++i) {
            addEdge(p[i], p[(i + 1) % cycleLen]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < 0.25) addEdge(p[i], p[j]);
            }
        }
    } else if (mode == 2) {
        // Several reciprocal pairs, which are compact two-cycles.
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());

        int pairs = rnd.next(1, n / 2);
        for (int i = 0; i < pairs; ++i) {
            addEdge(p[2 * i], p[2 * i + 1]);
            addEdge(p[2 * i + 1], p[2 * i]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && rnd.next() < 0.08) addEdge(p[i], p[j]);
            }
        }
    } else if (mode == 3) {
        // Dense small graph with many possible back edges.
        n = rnd.next(3, 9);
        double density = rnd.next(0.45, 0.9);
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (a != b && rnd.next() < density) addEdge(a, b);
            }
        }
    } else if (mode == 4) {
        // Disconnected mix: one cycle component and one acyclic component.
        n = rnd.next(3, 14);
        int split = rnd.next(2, n - 1);
        for (int i = 1; i < split; ++i) addEdge(i, i + 1);
        addEdge(split, 1);

        for (int a = split + 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if (rnd.next() < 0.45) addEdge(a, b);
            }
        }
    } else {
        // Long path with a few back edges.
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());

        for (int i = 0; i + 1 < n; ++i) addEdge(p[i], p[i + 1]);
        int backEdges = rnd.next(1, min(5, n - 1));
        for (int i = 0; i < backEdges; ++i) {
            int to = rnd.next(0, n - 2);
            int from = rnd.next(to + 1, n - 1);
            addEdge(p[from], p[to]);
        }
    }

    if (edgeSet.empty()) addEdge(1, 2);

    vector<pair<int, int>> edges(edgeSet.begin(), edgeSet.end());
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
