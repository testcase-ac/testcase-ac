#include "testlib.h"

#include <vector>
using namespace std;

int nextValue(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(1, 1000);
    return rnd.next(900000, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 4) {
        n = rnd.next(30, 60);
    } else {
        n = rnd.next(2, 12);
    }

    int valueMode = mode == 4 ? 2 : rnd.next(0, 1);
    int x = nextValue(valueMode);
    int y = nextValue(valueMode);

    vector<int> ga(n), gb(n), w(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 1) {
            ga[i] = rnd.next(1, 30);
            gb[i] = rnd.next(1, 30);
            w[i] = rnd.next(ga[i] + gb[i], 200);
        } else if (mode == 2) {
            ga[i] = rnd.next(1, 50);
            gb[i] = rnd.next(1, 50);
            int limiting = rnd.next(0, 1) ? ga[i] : gb[i];
            w[i] = rnd.next(limiting, limiting + 20);
        } else if (mode == 3) {
            ga[i] = rnd.next(1, 1000);
            gb[i] = rnd.next(1, 1000);
            w[i] = rnd.next(1, 1000000);
        } else if (mode == 4) {
            ga[i] = rnd.next(900000, 1000000);
            gb[i] = rnd.next(900000, 1000000);
            w[i] = rnd.next(900000, 1000000);
        } else {
            ga[i] = rnd.next(1, 20);
            gb[i] = rnd.next(1, 20);
            w[i] = rnd.next(1, 200);
        }
    }

    println(n, x, y);
    println(ga);
    println(gb);
    println(w);

    return 0;
}
