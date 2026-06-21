#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> randomInterval(int n, int mode) {
    if (mode == 0) {
        int x = rnd.next(1, n);
        return {x, x};
    }
    if (mode == 1) {
        int len = rnd.next(1, min(n, 4));
        int x1 = rnd.next(1, n - len + 1);
        return {x1, x1 + len - 1};
    }
    if (mode == 2) {
        int len = rnd.next(max(1, n / 2), n);
        int x1 = rnd.next(1, n - len + 1);
        return {x1, x1 + len - 1};
    }
    if (mode == 3) {
        return {1, n};
    }

    int x1 = rnd.next(1, n);
    int x2 = rnd.next(x1, n);
    return {x1, x2};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = 1;
        k = rnd.next(0, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        k = rnd.next(1, 16);
    } else if (mode == 2) {
        n = rnd.next(7, 25);
        k = rnd.next(1, 30);
    } else if (mode == 3) {
        n = rnd.next(10, 40);
        k = rnd.next(8, 45);
    } else {
        n = rnd.next(1, 30);
        k = rnd.next(0, 35);
    }

    vector<string> ops = {"R", "D", "H", "V"};
    vector<pair<string, pair<int, int>>> queries;
    queries.reserve(k);

    for (int i = 0; i < k; ++i) {
        int intervalMode;
        if (mode == 0) {
            intervalMode = 0;
        } else if (mode == 3 && i % 5 == 0) {
            intervalMode = 3;
        } else {
            intervalMode = rnd.next(0, 4);
        }

        string op;
        if (mode == 1) {
            op = ops[rnd.next(0, 3)];
        } else if (mode == 2) {
            op = ops[rnd.next(2, 3)];
        } else {
            op = rnd.any(ops);
        }

        queries.push_back({op, randomInterval(n, intervalMode)});
    }

    if (mode == 3) {
        shuffle(queries.begin(), queries.end());
    }

    println(n, k);
    for (const auto& query : queries) {
        println(query.first, query.second.first, query.second.second);
    }

    return 0;
}
