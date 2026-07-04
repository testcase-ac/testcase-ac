#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string makeRelation(int from, int to) {
    string s;
    s += char('A' + from);
    s += '<';
    s += char('A' + to);
    return s;
}

vector<pair<int, int>> chainRelations(const vector<int>& order) {
    vector<pair<int, int>> edges;
    for (int i = 0; i + 1 < int(order.size()); ++i) {
        edges.push_back({order[i], order[i + 1]});
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int instances = rnd.next(1, 5);
    for (int tc = 0; tc < instances; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(2, 8);

        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());

        vector<pair<int, int>> edges;

        if (mode == 0) {
            edges = chainRelations(order);
            int extra = rnd.next(0, min(6, n * (n - 1) / 2));
            for (int i = 0; i < extra; ++i) {
                int a = rnd.next(0, n - 2);
                int b = rnd.next(a + 1, n - 1);
                edges.push_back({order[a], order[b]});
            }
        } else if (mode == 1) {
            int used = rnd.next(2, n);
            for (int i = 0; i + 1 < used; ++i) {
                edges.push_back({order[i], order[i + 1]});
            }
            if (used == n && n > 2) {
                edges.pop_back();
            }
        } else if (mode == 2) {
            int cycleSize = rnd.next(2, min(n, 5));
            for (int i = 0; i < cycleSize; ++i) {
                edges.push_back({order[i], order[(i + 1) % cycleSize]});
            }
            int extra = rnd.next(0, 3);
            for (int i = 0; i < extra; ++i) {
                edges.push_back({rnd.next(0, n - 1), rnd.next(0, n - 1)});
            }
        } else if (mode == 3) {
            int repeated = rnd.next(0, n - 1);
            int target = rnd.next(0, n - 1);
            edges.push_back({repeated, target});
            edges.push_back({repeated, target});
            int extra = rnd.next(0, 4);
            for (int i = 0; i < extra; ++i) {
                edges.push_back({rnd.next(0, n - 1), rnd.next(0, n - 1)});
            }
        } else {
            int self = rnd.next(0, n - 1);
            edges.push_back({self, self});
            int extra = rnd.next(0, 4);
            for (int i = 0; i < extra; ++i) {
                int a = rnd.next(0, n - 1);
                int b = rnd.next(0, n - 1);
                edges.push_back({a, b});
            }
        }

        if (edges.empty()) {
            edges.push_back({0, 1});
        }
        shuffle(edges.begin(), edges.end());

        println(n, int(edges.size()));
        for (auto [from, to] : edges) {
            println(makeRelation(from, to));
        }
    }

    println(0, 0);
    return 0;
}
