#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    int k = rnd.next(1, n);

    vector<int> state(n + 1, 0);
    vector<int> cities(n);
    iota(cities.begin(), cities.end(), 1);
    shuffle(cities.begin(), cities.end());

    for (int i = 1; i <= k; ++i) {
        state[cities[i - 1]] = i;
    }
    for (int i = k; i < n; ++i) {
        if (mode == 1) {
            state[cities[i]] = rnd.next(1, min(k, 2));
        } else if (mode == 2) {
            state[cities[i]] = rnd.next(1, k);
        } else {
            state[cities[i]] = rnd.wnext(k, -2) + 1;
        }
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            candidates.push_back({u, v});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    set<pair<int, int>> chosen;
    auto addEdge = [&](int u, int v) {
        if (u > v) {
            swap(u, v);
        }
        if (u != v) {
            chosen.insert({u, v});
        }
    };

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            addEdge(rnd.next(1, v - 1), v);
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            addEdge(i - 1, i);
        }
    } else if (mode == 3) {
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (state[u] == state[v] || rnd.next(0, 3) == 0) {
                    addEdge(u, v);
                }
            }
        }
    } else if (mode == 4) {
        addEdge(rnd.next(1, n - 1), rnd.next(2, n));
    }

    int target = rnd.next(1, min<int>(candidates.size(), mode == 2 ? n + 3 : 2 * n));
    if (mode == 3) {
        int high = min<int>(candidates.size(), 3 * n);
        int low = min(high, max(1, n));
        target = rnd.next(low, high);
    }
    for (auto [u, v] : candidates) {
        if ((int)chosen.size() >= target) {
            break;
        }
        if (mode == 2 && rnd.next(0, 2) == 0 && state[u] != state[v]) {
            continue;
        }
        addEdge(u, v);
    }

    vector<pair<int, int>> edges(chosen.begin(), chosen.end());
    shuffle(edges.begin(), edges.end());

    int q = rnd.next(1, 12);
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; ++i) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) {
            ++b;
        }
        if (mode == 1 && rnd.next(0, 1) == 0) {
            vector<int> same;
            for (int city = 1; city <= n; ++city) {
                if (city != a && state[city] == state[a]) {
                    same.push_back(city);
                }
            }
            if (!same.empty()) {
                b = rnd.any(same);
            }
        }
        queries.push_back({a, b});
    }

    println(n, (int)edges.size(), k);
    for (auto [u, v] : edges) {
        println(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << state[i];
    }
    cout << '\n';
    println(q);
    for (auto [a, b] : queries) {
        println(a, b);
    }

    return 0;
}
