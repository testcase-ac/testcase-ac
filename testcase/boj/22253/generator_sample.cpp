#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(2, 15));

    vector<pair<int, int>> edges;
    if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i - 1, i);
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(1, i);
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int i = 2; i <= spine; ++i) {
            edges.emplace_back(i - 1, i);
        }
        for (int i = spine + 1; i <= n; ++i) {
            edges.emplace_back(rnd.next(1, spine), i);
        }
    } else if (mode == 4) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i / 2, i);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(rnd.next(1, i - 1), i);
        }
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 2, label.end());

    int digitMode = rnd.next(0, 4);
    vector<int> digit(n + 1);
    int base = rnd.next(0, 9);
    for (int i = 1; i <= n; ++i) {
        if (digitMode == 0) {
            digit[i] = rnd.next(0, 9);
        } else if (digitMode == 1) {
            digit[i] = (base + i - 1) % 10;
        } else if (digitMode == 2) {
            digit[i] = (base - i + 20) % 10;
        } else if (digitMode == 3) {
            digit[i] = rnd.next(max(0, base - 1), min(9, base + 1));
        } else {
            digit[i] = (i % 2 == 0 ? rnd.next(0, 3) : rnd.next(6, 9));
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }

    vector<int> outputDigit(n + 1);
    for (int i = 1; i <= n; ++i) {
        outputDigit[label[i]] = digit[i];
    }

    println(n);
    vector<int> line;
    for (int i = 1; i <= n; ++i) {
        line.push_back(outputDigit[i]);
    }
    println(line);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
