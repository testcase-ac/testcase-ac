#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        vector<int> edges = {0, 1, 2, 3, 4, 5, maxN};
        n = rnd.any(edges);
    } else if (mode == 1) {
        n = rnd.next(0, 30);
    } else if (mode == 2) {
        int side = rnd.next(2, 40);
        int delta = rnd.next(-2, 2);
        n = side * side + delta;
    } else if (mode == 3) {
        int side = rnd.next(30, 1000);
        int span = min(side + 2, 2000);
        n = side * side + rnd.next(-span, span);
    } else if (mode == 4) {
        n = rnd.next(maxN - 50000, maxN);
    } else {
        n = rnd.wnext(maxN + 1, rnd.next(-3, 3));
    }

    n = max(0, min(maxN, n));
    println(n);

    return 0;
}
