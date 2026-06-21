#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int kMax = 1000000000;
    int mode = rnd.next(0, 7);
    pair<int, int> nm;

    if (mode == 0) {
        int n = rnd.next(1, kMax);
        nm = {n, n};
    } else if (mode == 1) {
        nm = {1, rnd.next(1, kMax)};
    } else if (mode == 2) {
        nm = {rnd.next(2, 50), rnd.next(2, 50)};
    } else if (mode == 3) {
        int base = rnd.next(2, 200000);
        int a = rnd.next(1, 20);
        int b = rnd.next(1, 20);
        nm = {base * a + 1, base * b + 1};
    } else if (mode == 4) {
        int n = rnd.next(kMax - 100000, kMax);
        int m = rnd.next(kMax - 100000, kMax);
        nm = {n, m};
    } else if (mode == 5) {
        int n = rnd.next(2, 1000000);
        int step = rnd.next(1, 1000);
        nm = {n, min(kMax, n + step)};
    } else if (mode == 6) {
        int n = rnd.next(2, 100000);
        int m = rnd.next(2, 100000);
        while (__gcd(n - 1, m - 1) != 1) {
            n = rnd.next(2, 100000);
            m = rnd.next(2, 100000);
        }
        nm = {n, m};
    } else {
        int small = rnd.next(2, 1000);
        int large = rnd.next(kMax - 1000000, kMax);
        nm = {small, large};
    }

    if (rnd.next(0, 1)) swap(nm.first, nm.second);
    println(nm.first, nm.second);

    return 0;
}
