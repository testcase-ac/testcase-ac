#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 111222;
    int mode = rnd.next(6);
    int n;

    if (mode == 0) {
        vector<int> boundary = {0, 1, 2, 3, 7, maxN - 1, maxN};
        n = rnd.any(boundary);
    } else if (mode == 1) {
        n = rnd.next(0, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 500);
    } else if (mode == 3) {
        int base = 1 << rnd.next(0, 16);
        int delta = rnd.next(-3, 3);
        n = max(0, min(maxN, base + delta));
    } else if (mode == 4) {
        int base = rnd.next(maxN - 1000, maxN);
        n = max(0, min(maxN, base + rnd.next(-20, 20)));
    } else {
        n = rnd.next(0, maxN);
    }

    println(n);
    return 0;
}
