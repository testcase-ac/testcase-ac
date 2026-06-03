#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(2, 35));
    int capital = rnd.next(1, n);

    vector<pair<int, int>> edges;
    if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i - 1, i});
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            if (i != capital) {
                edges.push_back({capital, i});
            }
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i / 2, i});
        }
    } else if (mode == 4) {
        int spine = rnd.next(2, n);
        for (int i = 2; i <= spine; ++i) {
            edges.push_back({i - 1, i});
        }
        for (int i = spine + 1; i <= n; ++i) {
            edges.push_back({rnd.next(1, spine), i});
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            int bias = rnd.next(0, 2);
            int parent;
            if (bias == 0) {
                parent = 1;
            } else if (bias == 1) {
                parent = i - 1;
            } else {
                parent = rnd.next(1, i - 1);
            }
            edges.push_back({parent, i});
        }
    }

    for (auto& edge : edges) {
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    vector<int> leaves;
    vector<int> degree(n + 1, 0);
    for (auto [a, b] : edges) {
        ++degree[a];
        ++degree[b];
    }
    for (int i = 1; i <= n; ++i) {
        if (n == 1 || degree[i] == 1) {
            leaves.push_back(i);
        }
    }

    int q = rnd.next(1, 60);
    vector<pair<int, int>> queries;
    bool hasRead = false;
    for (int i = 0; i < q; ++i) {
        int type;
        if (i == q - 1 && !hasRead) {
            type = 2;
        } else {
            type = rnd.next(1, 100) <= 45 ? 1 : 2;
        }
        hasRead = hasRead || type == 2;

        int selector = rnd.next(0, 4);
        int city;
        if (selector == 0) {
            city = capital;
        } else if (selector == 1) {
            city = 1;
        } else if (selector == 2) {
            city = n;
        } else if (selector == 3) {
            city = rnd.any(leaves);
        } else {
            city = rnd.next(1, n);
        }
        queries.push_back({type, city});
    }

    println(n, capital);
    for (auto [a, b] : edges) {
        println(a, b);
    }
    println(q);
    for (auto [type, city] : queries) {
        println(type, city);
    }

    return 0;
}
