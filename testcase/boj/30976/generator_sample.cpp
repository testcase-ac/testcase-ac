#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int bounded(int x) {
    return max(1, min(300, x));
}

vector<int> randomValues(int n, int lo, int hi) {
    vector<int> values(n);
    for (int& x : values) x = rnd.next(lo, hi);
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 4 ? 6 : 18);
    int m = rnd.next(1, mode == 4 ? 24 : 18);

    vector<int> g(n), b(m), l(n), u(m);

    if (mode == 0) {
        g = randomValues(n, 1, 140);
        b = randomValues(m, 161, 300);
        l = randomValues(n, 1, 160);
        u = randomValues(m, 141, 300);
    } else if (mode == 1) {
        g = randomValues(n, 201, 300);
        b = randomValues(m, 1, 100);
        l = randomValues(n, 101, 300);
        u = randomValues(m, 1, 200);
    } else if (mode == 2) {
        int center = rnd.next(60, 240);
        for (int& x : g) x = bounded(center + rnd.next(-18, 30));
        for (int& x : b) x = bounded(center + rnd.next(-30, 18));
        for (int& x : l) x = bounded(center + rnd.next(-10, 28));
        for (int& x : u) x = bounded(center + rnd.next(-28, 10));
    } else if (mode == 3) {
        vector<int> girls = {1, 150, 300, rnd.next(1, 300)};
        vector<int> boys = {1, 149, 151, 300, rnd.next(1, 300)};
        for (int& x : g) x = rnd.any(girls);
        for (int& x : b) x = rnd.any(boys);
        for (int& x : l) x = rnd.any(girls);
        for (int& x : u) x = rnd.any(boys);
    } else if (mode == 4) {
        n = rnd.next(1, 5);
        m = rnd.next(12, 32);
        g = randomValues(n, 120, 300);
        b = randomValues(m, 1, 220);
        l = randomValues(n, 80, 300);
        u = randomValues(m, 1, 260);
    } else {
        n = rnd.next(12, 32);
        m = rnd.next(1, 5);
        g = randomValues(n, 40, 300);
        b = randomValues(m, 1, 260);
        l = randomValues(n, 40, 300);
        u = randomValues(m, 1, 260);
    }

    if (rnd.next(0, 3) == 0) shuffle(g.begin(), g.end());
    if (rnd.next(0, 3) == 0) shuffle(b.begin(), b.end());
    if (rnd.next(0, 3) == 0) shuffle(l.begin(), l.end());
    if (rnd.next(0, 3) == 0) shuffle(u.begin(), u.end());

    println(n, m);
    println(g);
    println(b);
    println(l);
    println(u);

    return 0;
}
