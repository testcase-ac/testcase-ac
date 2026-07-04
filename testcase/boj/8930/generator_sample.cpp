#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<int> makeWeights(int n, int mode) {
    vector<int> u(n);

    if (mode == 0) {
        int value = rnd.next(1, 40);
        fill(u.begin(), u.end(), value);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) u[i] = rnd.next(1, 25);
        int heavy = rnd.next(0, n - 1);
        u[heavy] = rnd.next(5000, 10000);
    } else if (mode == 2) {
        int current = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            current += rnd.next(0, 8);
            u[i] = current;
        }
        if (rnd.next(0, 1)) reverse(u.begin(), u.end());
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) u[i] = rnd.next(9000, 10000);
    } else {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 30) {
                u[i] = rnd.next(1, 3);
            } else {
                u[i] = rnd.next(10, 300);
            }
        }
    }

    shuffle(u.begin(), u.end());
    return u;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(4, 8);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = tc % 5;
        int n;
        int w;

        if (mode == 0) {
            n = rnd.next(1, 8);
            w = 1;
        } else if (mode == 1) {
            n = rnd.next(2, 10);
            w = n;
        } else if (mode == 2) {
            n = rnd.next(8, 18);
            w = rnd.next(2, n - 1);
        } else if (mode == 3) {
            n = rnd.next(20, 35);
            w = rnd.next(1, min(n, 6));
        } else {
            n = rnd.next(3, 25);
            w = rnd.next(1, n);
        }

        println(n, w);
        println(makeWeights(n, mode));
    }

    return 0;
}
