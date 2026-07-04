#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxK = 1000000000000000000LL;

    int mode = rnd.next(0, 5);
    int d;
    long long k;

    if (mode == 0) {
        d = 2;
        k = rnd.next(1LL, min(10LL, maxK));
    } else if (mode == 1) {
        d = 2 * rnd.next(1, 12);
        k = rnd.next(1LL, 100LL);
    } else if (mode == 2) {
        d = 2 * rnd.next(13, 100);
        k = rnd.next(1LL, 1000000LL);
    } else if (mode == 3) {
        d = 2 * rnd.next(1, 100000);
        k = rnd.next(1LL, maxK);
    } else if (mode == 4) {
        d = 2 * rnd.next(1, 100000);
        k = maxK - rnd.next(0LL, 1000000LL);
    } else {
        vector<int> edgeD = {2, 4, 6, 12, 34, 70, 200000};
        d = rnd.any(edgeD);
        vector<long long> edgeK = {1LL, 2LL, 22LL, 1000000000LL, maxK};
        k = rnd.any(edgeK);
    }

    println(d, k);
    return 0;
}
