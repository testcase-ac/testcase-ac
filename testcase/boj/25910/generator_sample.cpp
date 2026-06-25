#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

const int MAX_HEADER = (1 << 20) - 1;

int randomHeader() {
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        return 0;
    }
    if (mode == 1) {
        return MAX_HEADER;
    }
    if (mode == 2) {
        return 1 << rnd.next(0, 19);
    }
    if (mode == 3) {
        return rnd.next(0, 31);
    }
    if (mode == 4) {
        int bit = rnd.next(0, 19);
        return MAX_HEADER ^ (1 << bit);
    }
    return rnd.next(0, MAX_HEADER);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(3, 14);
    }

    vector<tuple<int, int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        int parent = 1;
        if (mode == 1) {
            parent = v - 1;
        } else if (mode == 2) {
            parent = 1;
        } else if (mode == 3) {
            parent = v / 2;
        } else if (mode == 4) {
            parent = rnd.next(1, v - 1);
        }
        edges.emplace_back(parent, v, randomHeader());
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    int x = randomHeader();
    println(n, x);
    for (auto [a, b, c] : edges) {
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        println(label[a], label[b], c);
    }

    return 0;
}
