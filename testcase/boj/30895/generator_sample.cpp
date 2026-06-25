#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampInt(long long value, int lo, int hi) {
    return (int)max((long long)lo, min((long long)hi, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int X;
    int Y;
    int K;

    if (mode == 0) {
        X = rnd.next(1, 20);
        Y = rnd.next(1, 20);
        K = rnd.next(1, 200);
    } else if (mode == 1) {
        X = rnd.next(1, 1000000);
        Y = X;
        K = rnd.next(1, 1000000000);
    } else if (mode == 2) {
        X = rnd.next(1, 50);
        Y = rnd.next(500000, 1000000);
        K = rnd.next(1, 1000000000);
    } else if (mode == 3) {
        X = rnd.next(500000, 1000000);
        Y = rnd.next(1, 50);
        K = rnd.next(1, 1000000000);
    } else if (mode == 4) {
        X = rnd.next(1, 1000000);
        Y = rnd.next(1, 1000000);
        int step = X;
        long long q = rnd.next(0, 1000000000 / step);
        int delta = rnd.next(-3, 3);
        K = clampInt(q * step + delta, 1, 1000000000);
    } else if (mode == 5) {
        X = rnd.next(1, 1000000);
        Y = rnd.next(1, 1000000);
        int step = X + Y;
        long long q = rnd.next(0, 1000000000 / step);
        int delta = rnd.next(-3, 3);
        K = clampInt(q * step + delta, 1, 1000000000);
    } else if (mode == 6) {
        vector<int> edges = {1, 2, 3, 999999, 1000000};
        X = rnd.any(edges);
        Y = rnd.any(edges);
        K = rnd.any(vector<int>{1, 2, 3, 999999999, 1000000000});
    } else {
        X = rnd.next(1, 1000000);
        Y = rnd.next(1, 1000000);
        K = rnd.next(900000000, 1000000000);
    }

    println(X, Y, K);
    return 0;
}
