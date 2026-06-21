#include "testlib.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace {

struct Edge {
    int u;
    int v;
    int w;
};

string cityName(int index) {
    return "C" + to_string(index);
}

void addEdge(vector<Edge>& edges, int u, int v, int w) {
    if (u > v) {
        swap(u, v);
    }
    edges.push_back({u, v, w});
}

void printCase(int n, vector<Edge> edges, int start, int destination) {
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(cityName(edge.u), cityName(edge.v), edge.w);
    }
    println(cityName(start), cityName(destination));
}

vector<Edge> makePathCase(int n) {
    vector<Edge> edges;
    int low = rnd.next(0, 20);
    int high = rnd.next(low, 10000);
    for (int i = 1; i < n; ++i) {
        int weight = rnd.next(low, high);
        if (i == rnd.next(1, n - 1)) {
            weight = low;
        }
        addEdge(edges, i, i + 1, weight);
    }
    return edges;
}

vector<Edge> makeDenseCase(int n) {
    vector<Edge> edges;
    int base = rnd.next(0, 9500);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (rnd.next(100) < 65 || j == i + 1) {
                addEdge(edges, i, j, min(10000, base + rnd.next(0, 500)));
            }
        }
    }
    return edges;
}

vector<Edge> makeDuplicateCase(int n) {
    vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
        addEdge(edges, i, i + 1, rnd.next(1, 10000));
    }

    int extra = rnd.next(1, n + 3);
    for (int i = 0; i < extra; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u) {
            ++v;
        }
        addEdge(edges, u, v, rnd.next(0, 10000));
    }
    return edges;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(1, 4);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 3);
        int n = rnd.next(2, 10);
        vector<Edge> edges;

        if (mode == 0) {
            edges = makePathCase(n);
        } else if (mode == 1) {
            edges = makeDenseCase(n);
        } else if (mode == 2) {
            edges = makeDuplicateCase(n);
        } else {
            edges = makePathCase(n);
            int shortcuts = rnd.next(1, n);
            for (int i = 0; i < shortcuts; ++i) {
                int u = rnd.next(1, n);
                int v = rnd.next(1, n - 1);
                if (v >= u) {
                    ++v;
                }
                addEdge(edges, u, v, rnd.next(0, 10000));
            }
        }

        int start = rnd.next(1, n);
        int destination = rnd.next(1, n - 1);
        if (destination >= start) {
            ++destination;
        }
        printCase(n, edges, start, destination);
    }

    println(0, 0);
    return 0;
}
