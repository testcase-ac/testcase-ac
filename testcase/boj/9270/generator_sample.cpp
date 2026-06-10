#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 999999999;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        int base = rnd.next(1, 50);
        int residue = rnd.next(0, 2);
        n = base * 3 + residue;
    } else if (mode == 2) {
        int base = rnd.next(1000, 100000);
        int residue = rnd.next(0, 2);
        n = base * 3 + residue;
    } else if (mode == 3) {
        n = maxN - rnd.next(0, 30);
    } else if (mode == 4) {
        vector<int> candidates = {
            1, 2, 3, 4, 5, 6, 8, 9,
            999999990, 999999991, 999999992,
            999999993, 999999994, 999999995,
            999999996, 999999997, 999999998,
            999999999
        };
        n = rnd.any(candidates);
    } else {
        n = rnd.next(1, maxN);
    }

    println(n);
    return 0;
}
