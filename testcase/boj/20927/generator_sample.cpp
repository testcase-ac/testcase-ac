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

int randomWeight(int flavor, int index) {
    if (flavor == 0) {
        return rnd.next(-20, 20);
    }
    if (flavor == 1) {
        return rnd.any(vector<int>{-1000000, -100, -1, 0, 1, 100, 1000000});
    }
    if (flavor == 2) {
        return index % 3 == 0 ? rnd.next(-5, 5) : rnd.next(-1000000, 1000000);
    }
    return rnd.next(-3, 3);
}

vector<pair<int, int>> allPairs(int n) {
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            pairs.push_back({a, b});
        }
    }
    return pairs;
}

vector<Edge> buildTree(int n, int flavor) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
        int u = order[i];
        int v = order[rnd.next(0, i - 1)];
        if (u > v) {
            swap(u, v);
        }
        edges.push_back({u, v, randomWeight(flavor, i)});
    }
    return edges;
}

vector<Edge> buildRandomGraph(int n, int m, int flavor) {
    vector<pair<int, int>> pairs = allPairs(n);
    shuffle(pairs.begin(), pairs.end());
    pairs.resize(m);

    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        edges.push_back({pairs[i].first, pairs[i].second, randomWeight(flavor, i)});
    }
    return edges;
}

vector<int> degreeCaps(int n, const vector<Edge>& edges, int mode) {
    vector<int> caps(n + 1, 0);
    vector<int> deg(n + 1, 0);
    for (const Edge& e : edges) {
        ++deg[e.a];
        ++deg[e.b];
    }

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            caps[i] = rnd.next(0, n - 1);
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            caps[i] = rnd.next(0, deg[i]);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            caps[i] = max(0, deg[i] - rnd.next(0, 1));
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            caps[i] = n - 1;
        }
        if (n > 1 && rnd.next(0, 2) == 0) {
            caps[rnd.next(1, n)] = rnd.next(0, 1);
        }
    }
    return caps;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<Edge> edges;

    if (mode == 0) {
        n = rnd.next(1, 4);
        int maxM = min(27, n * (n - 1) / 2);
        int m = rnd.next(0, maxM);
        edges = buildRandomGraph(n, m, rnd.next(0, 3));
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        edges = buildTree(n, rnd.next(0, 3));
    } else if (mode == 2) {
        n = rnd.next(3, 10);
        int maxM = min(27, n * (n - 1) / 2);
        int m = rnd.next(n - 1, maxM);
        edges = buildTree(n, rnd.next(0, 3));

        vector<pair<int, int>> pairs = allPairs(n);
        shuffle(pairs.begin(), pairs.end());
        for (const auto& p : pairs) {
            if ((int)edges.size() == m) {
                break;
            }
            bool used = false;
            for (const Edge& e : edges) {
                if (e.a == p.first && e.b == p.second) {
                    used = true;
                    break;
                }
            }
            if (!used) {
                edges.push_back({p.first, p.second, randomWeight(rnd.next(0, 3), (int)edges.size())});
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 10);
        int maxM = min(27, n * (n - 1) / 2);
        int m = rnd.next(0, min(maxM, n + rnd.next(0, 4)));
        edges = buildRandomGraph(n, m, rnd.next(0, 3));
    } else {
        n = rnd.next(8, 10);
        int maxM = min(27, n * (n - 1) / 2);
        int m = rnd.next(max(0, maxM - 5), maxM);
        edges = buildRandomGraph(n, m, 1);
    }

    shuffle(edges.begin(), edges.end());
    vector<int> caps = degreeCaps(n, edges, rnd.next(0, 3));

    println(n, (int)edges.size());
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << caps[i];
    }
    cout << '\n';
    for (const Edge& e : edges) {
        println(e.a, e.b, e.c);
    }

    return 0;
}
