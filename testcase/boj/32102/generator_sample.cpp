#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;

    if (mode == 0) {
        n = rnd.next(2, 5);
        m = rnd.next(2, 5);
    } else if (mode == 1) {
        n = rnd.next(2, 4);
        m = rnd.next(6, 15);
    } else if (mode == 2) {
        n = rnd.next(6, 15);
        m = rnd.next(2, 4);
    } else {
        n = rnd.next(3, 12);
        m = rnd.next(3, 12);
    }

    long long cells = 1LL * n * m;
    vector<long long> counts(3, 1);
    long long rem = cells - 3;

    if (mode == 0) {
        long long a = rnd.next(0LL, rem);
        long long b = rnd.next(0LL, rem - a);
        counts = {1 + a, 1 + b, 1 + rem - a - b};
    } else if (mode == 1) {
        long long dominant = rnd.next(max(1LL, cells / 2 - 2), cells - 2);
        long long rest = cells - dominant;
        long long second = rnd.next(1LL, rest - 1);
        counts = {dominant, second, rest - second};
    } else if (mode == 2) {
        long long dominant = (cells + 1) / 2;
        long long rest = cells - dominant;
        long long second = rnd.next(1LL, rest - 1);
        counts = {dominant, second, rest - second};
    } else if (mode == 3) {
        long long base = cells / 3;
        counts = {base, base, cells - 2 * base};
        for (int i = 0; i < 6; ++i) {
            int from = rnd.next(0, 2);
            int to = rnd.next(0, 2);
            if (from != to && counts[from] > 1) {
                --counts[from];
                ++counts[to];
            }
        }
    } else if (mode == 4) {
        long long rare = rnd.next(1LL, min(3LL, cells - 2));
        long long rest = cells - rare;
        long long first = rnd.next(1LL, rest - 1);
        counts = {rare, first, rest - first};
    } else {
        long long first = rnd.next(1LL, min(cells - 2, cells / 2 + 2));
        long long second = rnd.next(1LL, cells - first - 1);
        counts = {first, second, cells - first - second};
    }

    shuffle(counts.begin(), counts.end());

    println(n, m);
    println(counts);

    return 0;
}
