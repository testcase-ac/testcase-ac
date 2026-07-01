#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000LL;
    int mode = rnd.next(0, 5);
    long long n;

    if (mode == 0) {
        vector<long long> edges = {1, 2, 3, 4, 5, 6};
        n = rnd.any(edges);
    } else if (mode == 1) {
        n = rnd.next(7LL, 15LL);
    } else if (mode == 2) {
        n = rnd.next(16LL, 40LL);
    } else if (mode == 3) {
        n = rnd.next(41LL, 1000000LL);
    } else if (mode == 4) {
        n = maxN - rnd.next(0LL, 1000000LL);
    } else {
        n = rnd.next(1LL, maxN);
    }

    println(n);
    return 0;
}
