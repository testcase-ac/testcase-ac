#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int S = 1;
    int F = 1;

    if (mode == 0) {
        S = rnd.next(1, 738);
        F = S;
    } else if (mode == 1) {
        S = rnd.next(2, 738);
        F = S - 1;
    } else if (mode == 2) {
        S = rnd.next(1, 737);
        F = S + 1;
    } else if (mode == 3) {
        vector<int> edges = {1, 2, 737, 738};
        S = rnd.any(edges);
        F = rnd.any(edges);
    } else if (mode == 4) {
        int base = rnd.next(1, 738);
        int delta = rnd.next(-10, 10);
        S = base;
        F = min(738, max(1, base + delta));
    } else {
        S = rnd.next(1, 738);
        F = rnd.next(1, 738);
    }

    println(S);
    println(F);
    return 0;
}
