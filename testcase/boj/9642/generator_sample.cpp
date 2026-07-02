#include "testlib.h"
#include <vector>

using namespace std;

struct Query {
    int n;
    int x;
    int y;
};

int bounded(int value, int low, int high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

Query randomQuery(int preferredY) {
    int mode = rnd.next(0, 6);
    int n;
    int x;

    if (mode == 0) {
        n = rnd.any(vector<int>{1, 2, 3, 98, 99});
        x = rnd.any(vector<int>{1, 2, 99, 100});
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        x = rnd.next(1, 12);
    } else if (mode == 2) {
        n = rnd.next(90, 99);
        x = rnd.next(89, 100);
    } else if (mode == 3) {
        n = rnd.next(1, 99);
        x = bounded(n + rnd.next(-3, 3), 1, 100);
    } else {
        n = rnd.next(1, 99);
        x = rnd.next(1, 100);
    }

    int y = preferredY;
    if (y == 0) y = rnd.next(1, 2);

    return {n, x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Query> tests;
    tests.push_back({1, rnd.next(1, 100), rnd.next(1, 2)});
    tests.push_back({99, rnd.next(1, 100), rnd.next(1, 2)});
    tests.push_back({rnd.next(1, 99), 1, rnd.next(1, 2)});
    tests.push_back({rnd.next(1, 99), 100, rnd.next(1, 2)});
    tests.push_back({rnd.next(1, 99), rnd.next(1, 100), 1});
    tests.push_back({rnd.next(1, 99), rnd.next(1, 100), 2});

    int targetT = rnd.next(12, 40);
    while ((int)tests.size() < targetT) {
        int preferredY = 0;
        int bias = rnd.next(0, 5);
        if (bias == 0) preferredY = 1;
        if (bias == 1) preferredY = 2;
        tests.push_back(randomQuery(preferredY));
    }

    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (Query q : tests) {
        println(q.n, q.x, q.y);
    }

    return 0;
}
