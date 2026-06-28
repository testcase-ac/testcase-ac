#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 500000;
    int mode = rnd.next(0, 8);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(3, 20);
        k = rnd.next(2, n - 1);
    } else if (mode == 1) {
        n = rnd.next(4, 80);
        k = rnd.next(2, min(3, n - 1));
    } else if (mode == 2) {
        vector<int> powers;
        for (int x = 4; x <= maxN; x <<= 1) powers.push_back(x);
        n = rnd.any(powers);
        k = rnd.next(2, n - 1);
    } else if (mode == 3) {
        vector<int> beforePowers;
        for (int x = 4; x <= maxN; x <<= 1) beforePowers.push_back(x + 1);
        n = rnd.any(beforePowers);
        k = rnd.next(2, n - 1);
    } else if (mode == 4) {
        n = rnd.next(5, 200);
        k = rnd.next(4, n - 1);
    } else if (mode == 5) {
        n = rnd.next(1000, maxN);
        k = rnd.next(max(2, n - 20), n - 1);
    } else if (mode == 6) {
        n = rnd.next(maxN - 1000, maxN);
        k = rnd.next(2, n - 1);
    } else {
        int base = rnd.next(3, 700);
        n = base + rnd.next(0, 12);
        k = rnd.next(2, min(n - 1, base));
    }

    println(n, k);
    return 0;
}
