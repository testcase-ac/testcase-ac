#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 20);
    } else {
        n = rnd.next(2, 20);
        if (n % 2 == 1 && rnd.next(0, 1) == 0) {
            ++n;
        }
    }

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());

    vector<pair<int, int>> columns;
    int pos = 0;
    while (pos < n) {
        int remaining = n - pos;
        int len;
        if (remaining == 2) {
            len = 2;
        } else if (remaining == 3) {
            len = 3;
        } else if (mode == 0) {
            len = 2;
        } else if (mode == 1 && pos == 0) {
            len = remaining;
        } else if (mode == 3 && rnd.next(0, 99) < 65) {
            len = 2;
        } else {
            len = rnd.next(3, min(remaining, 7));
            if (remaining - len == 1) {
                ++len;
            }
        }

        vector<int> cycle(labels.begin() + pos, labels.begin() + pos + len);
        shuffle(cycle.begin(), cycle.end());

        if (len == 2) {
            columns.push_back({cycle[0], cycle[1]});
            columns.push_back({cycle[0], cycle[1]});
        } else {
            for (int i = 0; i < len; ++i) {
                columns.push_back({cycle[i], cycle[(i + 1) % len]});
            }
        }

        pos += len;
    }

    shuffle(columns.begin(), columns.end());
    vector<int> top(n), bottom(n);
    for (int i = 0; i < n; ++i) {
        auto [a, b] = columns[i];
        if (rnd.next(0, 1) == 0) {
            swap(a, b);
        }
        top[i] = a;
        bottom[i] = b;
    }

    println(n);
    println(top);
    println(bottom);

    return 0;
}
