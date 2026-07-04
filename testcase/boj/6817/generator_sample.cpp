#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

using Edge = tuple<int, int, int>;

vector<int> shuffledCities(int n) {
    vector<int> cities;
    for (int i = 1; i <= n; ++i) cities.push_back(i);
    shuffle(cities.begin(), cities.end());
    return cities;
}

void addEdge(vector<Edge>& edges, int x, int y, int cost) {
    edges.emplace_back(x, y, cost);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 5 ? rnd.next(10, 14) : rnd.next(1, 9);
    int destination = rnd.next(1, n);
    vector<Edge> edges;

    if (mode == 0) {
        // Sparse graph, including the valid one-city no-route case.
        if (n > 1) {
            int m = rnd.next(0, min(2 * n, n * (n - 1) / 2));
            set<pair<int, int>> used;
            while ((int)used.size() < m) {
                int x = rnd.next(1, n);
                int y = rnd.next(1, n);
                if (x == y) continue;
                if (x > y) swap(x, y);
                if (!used.insert({x, y}).second) continue;
                addEdge(edges, x, y, rnd.next(0, 30));
            }
        }
    } else if (mode == 1) {
        // Path with a few shortcuts to exercise multi-hop shipping choices.
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(0, 25));
        }
        int extra = n <= 2 ? 0 : rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n);
            if (x == y) {
                --i;
                continue;
            }
            addEdge(edges, x, y, rnd.next(0, 40));
        }
    } else if (mode == 2) {
        // Star centered at the destination, with some equal and zero costs.
        for (int city = 1; city <= n; ++city) {
            if (city != destination) {
                addEdge(edges, destination, city, rnd.next(0, 12));
            }
        }
        int extra = n <= 2 ? 0 : rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n);
            if (x == y) {
                --i;
                continue;
            }
            addEdge(edges, x, y, rnd.next(0, 12));
        }
    } else if (mode == 3) {
        // Deliberately duplicate some routes with different costs.
        int base = max(0, n - 1);
        for (int i = 1; i < n; ++i) {
            int cost = rnd.next(1, 50);
            addEdge(edges, i, i + 1, cost);
            if (rnd.next(0, 1)) {
                addEdge(edges, i + 1, i, rnd.next(0, cost));
            }
        }
        int extra = n == 1 ? 0 : rnd.next(0, max(1, base));
        for (int i = 0; i < extra; ++i) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n);
            if (x == y) {
                --i;
                continue;
            }
            addEdge(edges, x, y, rnd.next(0, 60));
        }
    } else if (mode == 4) {
        // Two components are valid; at least one store can still be local.
        int split = n == 1 ? 1 : rnd.next(1, n - 1);
        for (int i = 1; i < split; ++i) addEdge(edges, i, i + 1, rnd.next(1, 20));
        for (int i = split + 1; i < n; ++i) addEdge(edges, i, i + 1, rnd.next(1, 20));
        if (rnd.next(0, 2) == 0 && n > 2) {
            int x = rnd.next(1, split);
            int y = rnd.next(split + 1, n);
            if (x != y) addEdge(edges, x, y, rnd.next(30, 100));
        }
    } else {
        // Denser small graph with shuffled city labels.
        int density = rnd.next(25, 75);
        for (int x = 1; x <= n; ++x) {
            for (int y = x + 1; y <= n; ++y) {
                if (rnd.next(0, 99) < density) {
                    addEdge(edges, x, y, rnd.next(0, 100));
                }
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    vector<int> storeCities = shuffledCities(n);
    int k = rnd.next(1, n);
    storeCities.resize(k);
    if (find(storeCities.begin(), storeCities.end(), destination) ==
        storeCities.end() && rnd.next(0, 2) == 0) {
        storeCities[rnd.next(0, k - 1)] = destination;
    }
    shuffle(storeCities.begin(), storeCities.end());

    println(n);
    println((int)edges.size());
    for (const Edge& edge : edges) {
        int x, y, cost;
        tie(x, y, cost) = edge;
        println(x, y, cost);
    }
    println(k);
    for (int city : storeCities) {
        int priceMode = rnd.next(0, 3);
        int price;
        if (priceMode == 0) {
            price = 0;
        } else if (priceMode == 1) {
            price = rnd.next(1, 30);
        } else if (priceMode == 2) {
            price = rnd.next(5000, 10000);
        } else {
            price = rnd.next(0, 10000);
        }
        println(city, price);
    }
    println(destination);

    return 0;
}
