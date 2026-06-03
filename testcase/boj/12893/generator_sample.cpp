#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    set<pair<int, int>> seen;
    vector<pair<int, int>> edges;

    auto addEdge = [&](int a, int b) {
        if (a == b) return;
        pair<int, int> e = minmax(a, b);
        if (seen.insert(e).second) edges.push_back({a, b});
    };

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        for (int i = 1; i < n; ++i) addEdge(i, i + 1);
    } else if (mode == 2) {
        n = rnd.next(4, 14);
        vector<int> left, right;
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 1) == 0) {
                left.push_back(i);
            } else {
                right.push_back(i);
            }
        }
        if (left.empty()) {
            left.push_back(right.back());
            right.pop_back();
        }
        if (right.empty()) {
            right.push_back(left.back());
            left.pop_back();
        }
        for (int a : left) {
            for (int b : right) {
                if (rnd.next(0, 99) < rnd.next(30, 80)) addEdge(a, b);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        int cycle = rnd.next(1, (n - 1) / 2) * 2 + 1;
        for (int i = 1; i <= cycle; ++i) addEdge(i, i % cycle + 1);
        for (int i = cycle + 1; i <= n; ++i) addEdge(i, rnd.next(1, i - 1));
    } else if (mode == 4) {
        n = rnd.next(3, 12);
        addEdge(1, 2);
        addEdge(2, 3);
        addEdge(1, 3);
        for (int i = 4; i <= n; ++i) {
            if (rnd.next(0, 1)) addEdge(i, rnd.next(1, i - 1));
        }
    } else {
        n = rnd.next(6, 14);
        for (int start = 1; start <= n; start += rnd.next(2, 5)) {
            int end = min(n, start + rnd.next(1, 4));
            for (int i = start; i < end; ++i) addEdge(i, i + 1);
            if ((end - start + 1) >= 3 && rnd.next(0, 2) == 0) addEdge(start, end);
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) label[i] = i;
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }
    shuffle(edges.begin(), edges.end());

    println(n, int(edges.size()));
    for (auto [a, b] : edges) println(a, b);

    return 0;
}
