#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    int m = rnd.next(1, 24);

    vector<pair<int, int>> edges;
    edges.reserve(max(0, n - 1));

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i - 1, i);
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(1, i);
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i / 2, i);
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            int parent = max(1, i - rnd.next(1, min(i - 1, 4)));
            edges.emplace_back(parent, i);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(rnd.next(1, i - 1), i);
        }
    }

    string breeds;
    breeds.reserve(n);
    int breedMode = rnd.next(0, 4);
    for (int i = 1; i <= n; ++i) {
        char breed;
        if (breedMode == 0) {
            breed = 'G';
        } else if (breedMode == 1) {
            breed = 'H';
        } else if (breedMode == 2) {
            breed = (i % 2 == 0 ? 'G' : 'H');
        } else if (breedMode == 3) {
            breed = (i <= (n + 1) / 2 ? 'G' : 'H');
        } else {
            breed = rnd.next(0, 1) == 0 ? 'G' : 'H';
        }
        breeds.push_back(breed);
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1) == 0) {
            swap(edge.first, edge.second);
        }
    }

    println(n, m);
    println(breeds);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    for (int i = 0; i < m; ++i) {
        int a;
        int b;
        int queryMode = rnd.next(0, 4);
        if (queryMode == 0) {
            a = b = rnd.next(1, n);
        } else if (queryMode == 1) {
            a = 1;
            b = rnd.next(1, n);
        } else if (queryMode == 2) {
            a = n;
            b = rnd.next(1, n);
        } else {
            a = rnd.next(1, n);
            b = rnd.next(1, n);
        }

        char preferred;
        if (queryMode == 4) {
            preferred = breeds[a - 1] == 'G' ? 'H' : 'G';
        } else if (rnd.next(0, 2) == 0) {
            preferred = breeds[a - 1];
        } else {
            preferred = rnd.next(0, 1) == 0 ? 'G' : 'H';
        }

        println(a, b, string(1, preferred));
    }

    return 0;
}
