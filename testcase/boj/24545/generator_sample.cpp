#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

void addPath(vector<pair<int, int>>& edges, int& nextVertex, int from, int length) {
    int previous = from;
    for (int i = 0; i < length; ++i) {
        int current = nextVertex++;
        edges.push_back({previous, current});
        previous = current;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> edges;
    int n = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(2, 18);
        for (int vertex = 2; vertex <= n; ++vertex) {
            edges.push_back({vertex - 1, vertex});
        }
    } else if (mode == 1) {
        n = rnd.next(4, 30);
        int nextVertex = 2;
        int remaining = n - 1;
        vector<int> armLengths(3, 1);
        remaining -= 3;
        while (remaining-- > 0) {
            ++armLengths[rnd.next(0, 2)];
        }
        for (int length : armLengths) {
            addPath(edges, nextVertex, 1, length);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 24);
        int center = 1;
        int degree = rnd.next(4, min(n - 1, 9));
        for (int vertex = 2; vertex <= degree + 1; ++vertex) {
            edges.push_back({center, vertex});
        }
        for (int vertex = degree + 2; vertex <= n; ++vertex) {
            edges.push_back({rnd.next(2, vertex - 1), vertex});
        }
    } else if (mode == 3) {
        int spine = rnd.next(3, 12);
        int leaves = rnd.next(2, 10);
        n = spine + leaves;
        for (int vertex = 2; vertex <= spine; ++vertex) {
            edges.push_back({vertex - 1, vertex});
        }
        int hub = rnd.next(1, spine);
        for (int vertex = spine + 1; vertex <= n; ++vertex) {
            edges.push_back({hub, vertex});
        }
    } else if (mode == 4) {
        n = rnd.next(7, 31);
        for (int vertex = 2; vertex <= n; ++vertex) {
            int parent = max(1, vertex / 2 + rnd.next(-1, 1));
            parent = min(parent, vertex - 1);
            edges.push_back({parent, vertex});
        }
    } else {
        n = rnd.next(2, 35);
        for (int vertex = 2; vertex <= n; ++vertex) {
            int bias = rnd.next(-2, 2);
            int parent = rnd.wnext(vertex - 1, bias) + 1;
            edges.push_back({parent, vertex});
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto [u, v] : edges) {
        if (rnd.next(0, 1) == 1) {
            swap(u, v);
        }
        println(label[u], label[v]);
    }

    return 0;
}
