#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int minN = 2;
    const int maxN = 4000000;
    int mode = rnd.next(0, 7);
    int n;

    if (mode == 0) {
        n = rnd.next(2, 12);
    } else if (mode == 1) {
        n = rnd.next(13, 200);
    } else if (mode == 2) {
        int base = rnd.next(1, 2000);
        n = base * base;
    } else if (mode == 3) {
        vector<int> powers;
        for (int x = 2; x <= maxN; x *= 2) {
            powers.push_back(x);
        }
        n = rnd.any(powers) + rnd.next(-2, 2);
    } else if (mode == 4) {
        n = rnd.next(999900, 1000100);
    } else if (mode == 5) {
        n = maxN - rnd.next(0, 200);
    } else if (mode == 6) {
        n = rnd.next(2, 2000000) * 2;
    } else {
        n = rnd.next(1, 1999999) * 2 + 1;
    }

    n = max(minN, min(maxN, n));
    println(n);

    return 0;
}
