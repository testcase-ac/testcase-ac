#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Triple {
    int a;
    int b;
    int c;
};

Triple makePossible(int mode) {
    if (mode == 0) {
        int a = rnd.next(1, 9999);
        int b = rnd.next(1, 10000 - a);
        return {a, b, a + b};
    }

    if (mode == 1) {
        int c = rnd.next(1, 9999);
        int b = rnd.next(1, 10000 - c);
        return {b + c, b, c};
    }

    if (mode == 2) {
        int c = rnd.next(1, 9999);
        int a = rnd.next(1, 10000 - c);
        return {a, a + c, c};
    }

    if (mode == 3) {
        int a = rnd.next(1, 100);
        int b = rnd.next(1, 10000 / a);
        return {a, b, a * b};
    }

    if (mode == 4) {
        int c = rnd.next(1, 100);
        int b = rnd.next(1, 10000 / c);
        return {b * c, b, c};
    }

    int c = rnd.next(1, 100);
    int a = rnd.next(1, 10000 / c);
    return {a, a * c, c};
}

bool isPossible(const Triple& t) {
    if (t.a + t.b == t.c) return true;
    if (t.a - t.b == t.c || t.b - t.a == t.c) return true;
    if (t.a * t.b == t.c) return true;
    if (t.a % t.b == 0 && t.a / t.b == t.c) return true;
    if (t.b % t.a == 0 && t.b / t.a == t.c) return true;
    return false;
}

Triple makeImpossible() {
    while (true) {
        int a = rnd.next(1, 10000);
        int b = rnd.next(1, 10000);
        int c = rnd.next(1, 10000);
        Triple t{a, b, c};
        if (!isPossible(t)) return t;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(12, 40);
    vector<Triple> tests;

    tests.push_back({1, 1, 1});
    tests.push_back({10000, 10000, 10000});
    tests.push_back({1, 10000, 9999});
    tests.push_back({9999, 1, 10000});
    tests.push_back({100, 100, 10000});
    tests.push_back({10000, 1, 10000});

    while ((int)tests.size() < n) {
        int bucket = rnd.next(0, 9);
        if (bucket < 6) {
            tests.push_back(makePossible(bucket));
        } else if (bucket == 6) {
            int x = rnd.next(2, 100);
            tests.push_back({x, x, x});
        } else {
            tests.push_back(makeImpossible());
        }
    }

    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (const Triple& t : tests) {
        println(t.a, t.b, t.c);
    }

    return 0;
}
