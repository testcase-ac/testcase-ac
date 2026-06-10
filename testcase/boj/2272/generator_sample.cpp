#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 2) {
        n = rnd.next(2, 8);
    } else if (mode <= 5) {
        n = rnd.next(9, 40);
    } else {
        n = rnd.next(41, 160);
    }

    int mMode = rnd.next(0, 6);
    int m;
    if (mMode == 0) {
        m = 0;
    } else if (mMode == 1) {
        m = rnd.next(1, 20);
    } else if (mMode == 2) {
        m = rnd.next(0, n * 3);
    } else if (mMode == 3) {
        m = 1 << rnd.next(0, 29);
    } else if (mMode == 4) {
        m = 1000000000;
    } else {
        m = rnd.next(0, 1000000000);
    }

    vector<int> lamps(n);
    int pattern = rnd.next(0, 7);
    if (pattern == 0) {
        for (int i = 0; i < n; i++) lamps[i] = 0;
    } else if (pattern == 1) {
        for (int i = 0; i < n; i++) lamps[i] = 1;
    } else if (pattern == 2) {
        lamps[rnd.next(0, n - 1)] = 1;
    } else if (pattern == 3) {
        int start = rnd.next(0, n - 1);
        int len = rnd.next(1, n);
        for (int i = 0; i < len; i++) lamps[(start + i) % n] = 1;
    } else if (pattern == 4) {
        int first = rnd.next(0, 1);
        for (int i = 0; i < n; i++) lamps[i] = (first + i) % 2;
    } else if (pattern == 5 && n >= 2) {
        int period = rnd.next(2, min(n, 8));
        int mask = rnd.next(1, (1 << period) - 1);
        for (int i = 0; i < n; i++) lamps[i] = (mask >> (i % period)) & 1;
    } else {
        int onesPercent = rnd.next(10, 90);
        for (int i = 0; i < n; i++) lamps[i] = rnd.next(0, 99) < onesPercent;
    }

    println(n, m);
    for (int lamp : lamps) println(lamp);
    return 0;
}
