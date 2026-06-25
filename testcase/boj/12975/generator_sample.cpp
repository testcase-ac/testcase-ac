#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    vector<int> xs;

    if (mode == 0) {
        int n = rnd.next(1, 3);
        xs.resize(n);
        for (int& x : xs) x = rnd.next(0, 15);
    } else if (mode == 1) {
        int n = rnd.next(4, 16);
        xs.resize(n, 0);
        int nonzero = rnd.next(1, min(n, 4));
        for (int i = 0; i < nonzero; ++i) xs[i] = rnd.next(1, 255);
    } else if (mode == 2) {
        int n = rnd.next(6, 24);
        int a = rnd.next(0, 255);
        int b = rnd.next(0, 255);
        int c = a ^ b;
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 5);
            if (pick <= 1) xs.push_back(a);
            else if (pick <= 3) xs.push_back(b);
            else xs.push_back(c);
        }
    } else if (mode == 3) {
        int n = rnd.next(8, 28);
        vector<int> pool = {1, 2, 4, 8, 16, 32, 64, 128, 255};
        for (int i = 0; i < n; ++i) {
            int x = rnd.any(pool);
            if (rnd.next(0, 3) == 0) x ^= rnd.next(0, 15);
            xs.push_back(x);
        }
    } else if (mode == 4) {
        int n = rnd.next(10, 35);
        int lo = rnd.next(128, 240);
        int hi = rnd.next(lo, 255);
        for (int i = 0; i < n; ++i) xs.push_back(rnd.next(lo, hi));
    } else if (mode == 5) {
        int n = rnd.next(12, 40);
        int mask = rnd.any(vector<int>{15, 31, 63, 127, 255});
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(0, mask);
            xs.push_back((i % 2 == 0) ? base : (base ^ mask));
        }
    } else if (mode == 6) {
        int n = rnd.next(30, 70);
        for (int i = 0; i < n; ++i) xs.push_back(rnd.next(0, 255));
    } else {
        int n = rnd.next(80, 100);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) xs.push_back(rnd.next(0, 7));
            else xs.push_back(rnd.next(0, 255));
        }
    }

    shuffle(xs.begin(), xs.end());
    println((int)xs.size());
    println(xs);

    return 0;
}
