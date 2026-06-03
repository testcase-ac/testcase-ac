#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace {

vector<string> makeNames(int n) {
    vector<string> names;
    names.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (i < 26) {
            names.push_back(string(1, static_cast<char>('a' + i)));
        } else {
            names.push_back("p" + to_string(i));
        }
    }
    shuffle(names.begin(), names.end());
    return names;
}

void addEdge(vector<pair<int, int>>& edges, int a, int b) {
    if (a != b) edges.push_back({a, b});
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 4 ? 30 : 12);
    vector<string> names = makeNames(n);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        int chain = rnd.next(2, n);
        for (int i = 0; i + 1 < chain; ++i) addEdge(edges, i, i + 1);
    } else if (mode == 1) {
        double density = rnd.next(0.15, 0.55);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < density) addEdge(edges, i, j);
            }
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i + 1 < split; ++i) addEdge(edges, i, i + 1);
        for (int i = split; i + 1 < n; ++i) {
            if (rnd.next(0, 1)) addEdge(edges, i, i + 1);
        }
    } else if (mode == 3) {
        int cycle = rnd.next(2, min(n, 6));
        for (int i = 0; i < cycle; ++i) addEdge(edges, i, (i + 1) % cycle);
        for (int i = cycle; i < n; ++i) {
            addEdge(edges, rnd.next(0, cycle - 1), i);
        }
    } else {
        for (int i = 1; i < n; ++i) addEdge(edges, rnd.next(0, i - 1), i);
        int extra = rnd.next(0, min(25, n * (n - 1) / 4));
        for (int k = 0; k < extra; ++k) {
            int a = rnd.next(0, n - 2);
            int b = rnd.next(a + 1, n - 1);
            addEdge(edges, a, b);
        }
    }

    shuffle(edges.begin(), edges.end());

    int q = rnd.next(1, 20);
    vector<pair<int, int>> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 2);
        if (b >= a) ++b;
        if (rnd.next(0, 1)) swap(a, b);
        queries.push_back({a, b});
    }

    println(n, static_cast<int>(edges.size()));
    for (const auto& [a, b] : edges) println(names[a], names[b]);
    println(q);
    for (const auto& [a, b] : queries) println(names[a], names[b]);
}
