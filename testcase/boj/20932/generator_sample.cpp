#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(2, 6);
        int digit = rnd.next(1, 9);
        a.assign(n, digit);
    } else if (mode == 1) {
        n = rnd.next(2, 16);
        int lo = rnd.next(1, 7);
        int hi = rnd.next(lo, 9);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 9);
        for (int digit = 1; digit <= 9; ++digit) {
            a.push_back(digit);
        }
        shuffle(a.begin(), a.end());
        a.resize(n);
    } else if (mode == 3) {
        n = rnd.next(8, 16);
        vector<int> pool = {1, 2, 3, 4, 6, 8, 9};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else if (mode == 4) {
        n = rnd.next(6, 16);
        vector<int> pool = {1, 3, 5, 7, 9};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else {
        n = rnd.next(10, 16);
        vector<int> pool = {1, 2, 5, 8};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    }

    shuffle(a.begin(), a.end());
    println(n);
    println(a);

    return 0;
}
