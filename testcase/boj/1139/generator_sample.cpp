#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    vector<int> lengths;

    if (mode == 0) {
        n = rnd.next(1, 2);
        int base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) lengths.push_back(base);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        int value = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(value);
            value = min(100, value + rnd.next(value, value + 4));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 16);
        int side = rnd.next(1, 100);
        lengths.assign(n, side);
    } else if (mode == 3) {
        n = rnd.next(3, 16);
        int a = rnd.next(1, 49);
        int b = rnd.next(a, 50);
        int c = rnd.next(a + b - 1, min(100, a + b + 1));
        lengths = {a, b, c};
        while ((int)lengths.size() < n) lengths.push_back(rnd.next(1, 100));
    } else if (mode == 4) {
        n = rnd.next(3, 16);
        int small = rnd.next(1, 6);
        int large = rnd.next(80, 100);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(rnd.next() < 0.45 ? rnd.next(1, small) : rnd.next(large, 100));
        }
    } else if (mode == 5) {
        n = rnd.next(3, 16);
        int lo = rnd.next(1, 80);
        int hi = rnd.next(lo, min(100, lo + rnd.next(0, 35)));
        for (int i = 0; i < n; ++i) lengths.push_back(rnd.next(lo, hi));
    } else {
        n = 16;
        for (int i = 0; i < n; ++i) {
            int band = rnd.next(0, 3);
            if (band == 0) lengths.push_back(rnd.next(1, 20));
            else if (band == 1) lengths.push_back(rnd.next(21, 70));
            else lengths.push_back(rnd.next(71, 100));
        }
    }

    shuffle(lengths.begin(), lengths.end());
    println(n);
    println(lengths);

    return 0;
}
