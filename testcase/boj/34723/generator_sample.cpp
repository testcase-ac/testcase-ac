#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int value(int p, int m, int c) {
    return (p + m) * (m + c);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int P, M, C;

    if (mode == 0) {
        P = rnd.next(1, 6);
        M = rnd.next(1, 6);
        C = rnd.next(1, 6);
    } else if (mode == 1) {
        P = rnd.next(1, 3);
        M = rnd.next(20, 100);
        C = rnd.next(1, 3);
    } else if (mode == 2) {
        P = rnd.next(20, 100);
        M = rnd.next(1, 3);
        C = rnd.next(20, 100);
    } else if (mode == 3) {
        P = rnd.next(80, 100);
        M = rnd.next(80, 100);
        C = rnd.next(80, 100);
    } else {
        P = rnd.next(1, 100);
        M = rnd.next(1, 100);
        C = rnd.next(1, 100);
    }

    vector<int> candidates;
    candidates.push_back(0);
    candidates.push_back(1);
    candidates.push_back(1000000000);
    candidates.push_back(value(1, 1, 1));
    candidates.push_back(value(P, M, C));

    for (int i = 0; i < 6; ++i) {
        int p = rnd.next(1, P);
        int m = rnd.next(1, M);
        int c = rnd.next(1, C);
        int delta = rnd.next(-20, 20);
        candidates.push_back(max(0, value(p, m, c) + delta));
    }

    int X;
    int xMode = rnd.next(0, 3);
    if (xMode == 0) {
        X = rnd.any(candidates);
    } else if (xMode == 1) {
        X = rnd.next(0, min(1000000000, value(P, M, C) + 200));
    } else {
        X = rnd.next(0, 1000000000);
    }

    println(P, M, C);
    println(X);

    return 0;
}
