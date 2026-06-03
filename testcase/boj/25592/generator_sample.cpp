#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 100000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        int k = rnd.next(1, 80);
        n = k * (k + 1) / 2;
    } else if (mode == 2) {
        int k = rnd.next(2, 80);
        n = k * (k + 1) / 2 - rnd.next(1, min(5, k));
    } else if (mode == 3) {
        int k = rnd.next(1, 79);
        n = k * (k + 1) / 2 + rnd.next(1, 5);
    } else if (mode == 4) {
        int k = rnd.next(400, 446);
        n = k * (k + 1) / 2 + rnd.next(-20, 20);
    } else {
        n = rnd.next(99900, maxN);
    }

    n = max(1, min(maxN, n));
    println(n);

    return 0;
}
