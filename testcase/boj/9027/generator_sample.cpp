#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeCoordinates(int n, int mode) {
    vector<int> x(n);
    if (mode == 0) {
        int start = rnd.next(1, 20);
        int step = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            x[i] = start + i * step;
        }
    } else if (mode == 1) {
        int cur = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            x[i] = cur;
            cur += rnd.next(1, 25);
        }
    } else if (mode == 2) {
        int cur = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            x[i] = cur;
            cur += rnd.next(i % 3 == 0 ? 20 : 1, i % 3 == 0 ? 80 : 8);
        }
    } else {
        int cur = rnd.next(99999000, 99999980 - n);
        for (int i = 0; i < n; ++i) {
            x[i] = cur++;
        }
    }
    return x;
}

vector<int> makeFans(int n, int mode) {
    vector<int> fans(n);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            fans[i] = rnd.next(1, 9);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            fans[i] = (i % 2 == 0) ? rnd.next(1, 3) : rnd.next(5000, 10000);
        }
    } else if (mode == 2) {
        int heavy = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            fans[i] = (i == heavy) ? rnd.next(8000, 10000) : rnd.next(1, 20);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            fans[i] = rnd.next(1, 4);
        }
        fans[0] = rnd.next(5000, 10000);
        fans[n - 1] = rnd.next(5000, 10000);
    }
    return fans;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0 && rnd.next(4) == 0) {
            n = 2;
        } else {
            n = rnd.next(3, 18);
        }

        int coordMode = rnd.next(4);
        int fanMode = rnd.next(4);
        vector<int> x = makeCoordinates(n, coordMode);
        vector<int> fans = makeFans(n, fanMode);

        println(n);
        println(x);
        println(fans);
    }

    return 0;
}
