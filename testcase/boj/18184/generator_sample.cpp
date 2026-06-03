#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 4);
        k = rnd.next(1, 1 << n);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        k = 1;
    } else if (mode == 2) {
        n = rnd.next(1, 12);
        k = 1 << n;
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        k = rnd.next((1 << n) - min(8, 1 << n), 1 << n);
    } else if (mode == 4) {
        n = rnd.next(1, 12);
        int bit = rnd.next(0, n);
        k = 1 << bit;
    } else if (mode == 5) {
        n = rnd.next(2, 12);
        int bits = rnd.next(1, min(n + 1, 5));
        vector<int> positions;
        for (int i = 0; i <= n; ++i) positions.push_back(i);
        shuffle(positions.begin(), positions.end());

        k = 0;
        for (int i = 0; i < bits; ++i) k += 1 << positions[i];
        if (k > (1 << n)) k = 1 << n;
    } else if (mode == 6) {
        n = rnd.next(3, 12);
        int base = 1 << rnd.next(1, n);
        int delta = rnd.next(-min(3, base - 1), 3);
        k = max(1, min(1 << n, base + delta));
    } else {
        n = rnd.next(1, 12);
        k = rnd.next(1, 1 << n);
    }

    println(n, k);
    return 0;
}
