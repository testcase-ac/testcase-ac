#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxA = 1000000000;
    int mode = rnd.next(0, 5);
    int a;

    if (mode == 0) {
        vector<int> edges = {1, 2, 3, 4, 5, maxA - 3, maxA - 2, maxA - 1, maxA};
        a = rnd.any(edges);
    } else if (mode == 1) {
        a = rnd.next(1, 30);
    } else if (mode == 2) {
        int residue = rnd.next(0, 3);
        int limit = (maxA - residue) / 4;
        int k = rnd.next(0, limit);
        a = 4 * k + residue;
        if (a == 0) a += 4;
    } else if (mode == 3) {
        int center = rnd.next(1, maxA / 4);
        a = 4 * center + rnd.next(-2, 2);
        a = max(1, min(maxA, a));
    } else if (mode == 4) {
        a = rnd.wnext(maxA, -4) + 1;
    } else {
        a = rnd.wnext(maxA, 4) + 1;
    }

    println(a);
    return 0;
}
