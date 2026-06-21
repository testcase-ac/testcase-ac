#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    vector<int> piles;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            piles.push_back(rnd.next(1, 8));
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 30);
        int value = rnd.next(1, 40);
        for (int i = 0; i < n; ++i) {
            piles.push_back(value);
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 25);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(3) == 0) {
                piles.push_back(rnd.next(1, 5));
            } else {
                piles.push_back(rnd.next(1900, 2000));
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 40);
        vector<int> values = {1, 2, 3, 4, 5, 16, 31, 64, 127, 256, 511, 1024, 1999, 2000};
        for (int i = 0; i < n; ++i) {
            piles.push_back(rnd.any(values));
        }
    } else {
        int n = rnd.next(20, 80);
        int lo = rnd.next(1, 1000);
        int hi = rnd.next(lo, 2000);
        for (int i = 0; i < n; ++i) {
            piles.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(piles.begin(), piles.end());
    println(static_cast<int>(piles.size()));
    println(piles);

    return 0;
}
