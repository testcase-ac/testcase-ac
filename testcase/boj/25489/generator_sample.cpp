#include "testlib.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

static string probability() {
    int value = rnd.next(0, 100);
    if (rnd.next(4) == 0) {
        value = rnd.any(vector<int>{0, 1, 25, 50, 75, 99, 100});
    }

    string cents = to_string(value);
    if (cents.size() == 1) cents = "0" + cents;
    return string(value == 100 ? "1" : "0") + "." + (value == 100 ? "00" : cents);
}

static vector<pair<int, int>> makeTree(int n) {
    int mode = rnd.next(5);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) edges.push_back({v - 1, v});
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) edges.push_back({center, v});
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) edges.push_back({v / 2, v});
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) edges.push_back({rnd.next(1, v - 1), v});
    } else {
        int spine = rnd.next(2, n);
        for (int v = 2; v <= spine; ++v) edges.push_back({v - 1, v});
        for (int v = spine + 1; v <= n; ++v) edges.push_back({rnd.next(1, spine), v});
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) label[i] = i;
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(2) == 0) swap(edge.first, edge.second);
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    if (rnd.next(5) == 0) n = rnd.next(15, 30);
    int q = rnd.next(1, min(24, n * 3));

    println(n);

    vector<string> p(n);
    for (string& value : p) value = probability();
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << p[i];
    }
    cout << '\n';

    for (const auto& edge : makeTree(n)) {
        println(edge.first, edge.second);
    }

    println(q);
    int hotVertex = rnd.next(1, n);
    for (int i = 0; i < q; ++i) {
        int u = (rnd.next(3) == 0 ? hotVertex : rnd.next(1, n));
        println(u, probability());
    }

    return 0;
}
