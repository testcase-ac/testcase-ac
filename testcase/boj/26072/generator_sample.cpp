#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_VALUE = 100000;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    int l = rnd.next(1, 100);
    vector<int> x;
    vector<int> w;

    if (mode == 0) {
        l = rnd.next(1, 20);
        x = {rnd.next(0, l)};
        w = {rnd.any(vector<int>{1, rnd.next(1, 100), MAX_VALUE})};
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        l = rnd.next(1, 100);
        x.resize(n);
        w.resize(n);
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(0, l);
            w[i] = rnd.any(vector<int>{1, rnd.next(1, 100), MAX_VALUE});
        }
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        l = rnd.next(1, 100);
        x.resize(n);
        w.resize(n);
        for (int i = 0; i < n; ++i) {
            x[i] = (rnd.next(0, 3) == 0 ? rnd.next(0, l) : rnd.any(vector<int>{0, l}));
            w[i] = rnd.next(1, 200);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 18);
        l = rnd.next(10, 200);
        int center = rnd.next(0, l);
        int radius = rnd.next(0, min(8, l));
        x.resize(n);
        w.resize(n);
        for (int i = 0; i < n; ++i) {
            x[i] = max(0, min(l, center + rnd.next(-radius, radius)));
            w[i] = rnd.next(1, 1000);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 16);
        l = rnd.next(1, 100);
        int shared = rnd.next(0, l);
        x.resize(n, shared);
        w.resize(n);
        for (int i = 0; i < n; ++i) {
            w[i] = rnd.next(1, MAX_VALUE);
        }
    } else if (mode == 5) {
        n = rnd.next(4, 30);
        l = rnd.next(20, 500);
        x.resize(n);
        w.resize(n);
        for (int i = 0; i < n; ++i) {
            x[i] = (i % 2 == 0 ? rnd.next(0, min(l, 10)) : rnd.next(max(0, l - 10), l));
            w[i] = (i % 2 == 0 ? rnd.next(1, 20) : rnd.next(1000, MAX_VALUE));
        }
    } else {
        n = rnd.next(20, 80);
        l = rnd.next(1000, MAX_VALUE);
        x.resize(n);
        w.resize(n);
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(0, l);
            w[i] = rnd.next(1, MAX_VALUE);
        }
    }

    vector<int> order((int)x.size());
    for (int i = 0; i < (int)order.size(); ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    vector<int> shuffledX, shuffledW;
    shuffledX.reserve(order.size());
    shuffledW.reserve(order.size());
    for (int idx : order) {
        shuffledX.push_back(x[idx]);
        shuffledW.push_back(w[idx]);
    }

    println((int)shuffledX.size(), l);
    println(shuffledX);
    println(shuffledW);

    return 0;
}
