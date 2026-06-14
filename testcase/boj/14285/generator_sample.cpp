#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    int c;
};

void addEdge(vector<Edge>& edges, int a, int b, int c) {
    if (rnd.next(2)) {
        swap(a, b);
    }
    edges.push_back({a, b, c});
}

int randomWeight(int mode) {
    if (mode == 0) {
        return rnd.next(1, 5);
    }
    if (mode == 1) {
        return rnd.any(vector<int>{1, 2, 3, 50, 75, 100});
    }
    return rnd.next(1, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 12);
    vector<Edge> edges;
    int s = 1;
    int t = n;

    if (mode == 0) {
        n = rnd.next(2, 10);
        s = 1;
        t = n;
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, randomWeight(1));
        }
    } else if (mode == 1) {
        n = rnd.next(3, 10);
        s = rnd.next(1, n);
        do {
            t = rnd.next(1, n);
        } while (t == s);

        for (int i = 1; i <= n; ++i) {
            addEdge(edges, i, i == n ? 1 : i + 1, randomWeight(2));
        }
        int extra = rnd.next(0, min(8, n * (n - 3) / 2));
        for (int i = 0; i < extra; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            while (a == b) {
                b = rnd.next(1, n);
            }
            addEdge(edges, a, b, randomWeight(i % 3));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 8);
        s = 1;
        t = n;
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, randomWeight(0));
        }
        int parallelGroups = rnd.next(1, 4);
        for (int i = 0; i < parallelGroups; ++i) {
            int a = rnd.next(1, n - 1);
            int copies = rnd.next(1, 4);
            for (int j = 0; j < copies; ++j) {
                addEdge(edges, a, a + 1, randomWeight(2));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 9);
        s = rnd.next(1, n);
        do {
            t = rnd.next(1, n);
        } while (t == s);

        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, randomWeight(1));
        }
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if (b != a + 1) {
                    candidates.push_back({a, b});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int extra = rnd.next(0, min<int>(candidates.size(), 16));
        for (int i = 0; i < extra; ++i) {
            addEdge(edges, candidates[i].first, candidates[i].second, randomWeight(2));
        }
    } else {
        int left = rnd.next(1, 5);
        int right = rnd.next(1, 5);
        n = left + right;
        s = rnd.next(1, left);
        t = rnd.next(left + 1, n);

        for (int i = 1; i < left; ++i) {
            addEdge(edges, i, i + 1, randomWeight(1));
        }
        for (int i = left + 1; i < n; ++i) {
            addEdge(edges, i, i + 1, randomWeight(1));
        }
        addEdge(edges, rnd.next(1, left), rnd.next(left + 1, n), randomWeight(2));

        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) {
            if (rnd.next(2) && left >= 2) {
                int a = rnd.next(1, left);
                int b = rnd.next(1, left);
                while (a == b) {
                    b = rnd.next(1, left);
                }
                addEdge(edges, a, b, randomWeight(i % 3));
            } else if (right >= 2) {
                int a = rnd.next(left + 1, n);
                int b = rnd.next(left + 1, n);
                while (a == b) {
                    b = rnd.next(left + 1, n);
                }
                addEdge(edges, a, b, randomWeight(i % 3));
            }
        }
    }

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());
    for (Edge& edge : edges) {
        edge.a = labels[edge.a - 1];
        edge.b = labels[edge.b - 1];
    }
    s = labels[s - 1];
    t = labels[t - 1];
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.c);
    }
    println(s, t);

    return 0;
}
