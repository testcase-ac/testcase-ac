#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxS = 100000;
    int mode = rnd.next(0, 5);
    int s = 1;

    if (mode == 0) {
        vector<int> edges = {1, 2, 3, 4, 5, 25, 83160, maxS};
        s = rnd.any(edges);
    } else if (mode == 1) {
        s = rnd.next(1, 200);
    } else if (mode == 2) {
        s = rnd.next(maxS - 200, maxS);
    } else if (mode == 3) {
        int a = rnd.next(1, 447);
        int b = rnd.next(1, 447);
        s = a * b;
        if (s > maxS) s = maxS - rnd.next(0, 999);
    } else if (mode == 4) {
        int len1 = rnd.next(1, 447);
        int len2 = rnd.next(1, 447);
        long long tri1 = 1LL * len1 * (len1 + 1) / 2;
        long long tri2 = 1LL * len2 * (len2 + 1) / 2;
        long long candidate = tri1 * tri2;
        if (candidate <= maxS) {
            s = (int)candidate;
        } else {
            s = rnd.next(1, maxS);
        }
    } else {
        int base = rnd.next(1, 316);
        s = base * base + rnd.next(0, base);
        if (s > maxS) s = maxS;
    }

    println(s);
    return 0;
}
