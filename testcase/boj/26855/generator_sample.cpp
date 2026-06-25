#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makeEdges(int n, int shape) {
    vector<pair<int, int>> edges;
    if (shape == 0) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({1, i});
        }
    } else if (shape == 1) {
        for (int i = 1; i < n; ++i) {
            edges.push_back({i, i + 1});
        }
    } else if (shape == 2) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i / 2, i});
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(1, i - 1), i});
        }
    }

    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int shape = rnd.next(0, 3);
    int weightMode = rnd.next(0, 4);

    vector<int> weights(n + 1);
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};

    if (weightMode == 0) {
        fill(weights.begin() + 1, weights.end(), 1);
    } else if (weightMode == 1) {
        int factor = rnd.any(primes);
        for (int i = 1; i <= n; ++i) {
            weights[i] = factor * rnd.next(1, 20);
        }
    } else if (weightMode == 2) {
        for (int i = 1; i <= n; ++i) {
            weights[i] = rnd.any(primes);
        }
    } else if (weightMode == 3) {
        int factor = rnd.any(primes);
        for (int i = 1; i <= n; ++i) {
            weights[i] = (rnd.next(0, 99) < 65) ? factor * rnd.next(1, 30)
                                                 : rnd.any(primes);
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            weights[i] = rnd.next(1, 100);
        }
        weights[rnd.next(1, n)] = 1000000;
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << weights[i];
    }
    cout << '\n';

    vector<pair<int, int>> edges = makeEdges(n, shape);
    for (auto [u, v] : edges) {
        if (u > v) {
            swap(u, v);
        }
        println(u, v);
    }

    return 0;
}
