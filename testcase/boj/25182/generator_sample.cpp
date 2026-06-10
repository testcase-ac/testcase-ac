#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 100000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(11, 100);
    } else if (mode == 2) {
        n = rnd.next(1000, 5000);
    } else if (mode == 3) {
        n = maxN - rnd.next(0, 20);
    } else if (mode == 4) {
        vector<int> bases = {1, 2, 3, 10, 100, 1000, 10000, maxN};
        int base = rnd.any(bases);
        n = base + rnd.next(-2, 2);
        if (n < 1) n = 1;
        if (n > maxN) n = maxN;
    } else {
        n = rnd.next(1, maxN);
    }

    println(n);
    return 0;
}
