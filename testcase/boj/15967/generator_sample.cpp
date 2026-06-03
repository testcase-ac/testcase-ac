#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Query {
    int type;
    int left;
    int right;
    int delta;
};

int randomValue(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(1499990, 1500000);
    if (mode == 2) return rnd.any(vector<int>{1, 2, 1499999, 1500000});
    return rnd.next(1, 1500000);
}

pair<int, int> randomInterval(int n, int mode) {
    if (mode == 0) {
        int pos = rnd.next(1, n);
        return {pos, pos};
    }
    if (mode == 1) return {1, n};
    if (mode == 2) {
        int right = rnd.next(1, n);
        return {1, right};
    }
    int left = rnd.next(1, n);
    int right = rnd.next(left, n);
    return {left, right};
}

int randomDelta(int mode) {
    if (mode == 0) return rnd.next(-5, 5);
    if (mode == 1) return rnd.any(vector<int>{-1000, -999, 0, 999, 1000});
    return rnd.next(-1000, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else {
        n = rnd.next(3, 20);
    }

    int q1 = 0;
    int q2 = 0;
    if (mode == 0) {
        q1 = rnd.next(0, 4);
        q2 = rnd.next(0, 4);
    } else if (mode == 1) {
        q2 = rnd.next(1, 10);
    } else if (mode == 2) {
        q1 = rnd.next(1, 10);
        q2 = rnd.next(1, 10);
    } else if (mode == 3) {
        q1 = rnd.next(5, 15);
        q2 = rnd.next(1, 15);
    } else {
        q1 = rnd.next(0, 15);
        q2 = rnd.next(0, 15);
    }

    vector<int> a(n);
    int valueMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) a[i] = randomValue(valueMode);

    vector<Query> queries;
    for (int i = 0; i < q1; ++i) {
        int intervalMode = (mode == 4 ? 2 : rnd.next(0, 3));
        auto [left, right] = randomInterval(n, intervalMode);
        queries.push_back({2, left, right, randomDelta(rnd.next(0, 2))});
    }
    for (int i = 0; i < q2; ++i) {
        int intervalMode = rnd.next(0, 3);
        auto [left, right] = randomInterval(n, intervalMode);
        queries.push_back({1, left, right, 0});
    }
    shuffle(queries.begin(), queries.end());

    println(n, q1, q2);
    println(a);
    for (const Query& query : queries) {
        if (query.type == 1) {
            println(query.type, query.left, query.right);
        } else {
            println(query.type, query.left, query.right, query.delta);
        }
    }

    return 0;
}
