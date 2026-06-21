#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxA = 1000000000000000000LL;
    long long a;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        a = rnd.next(1LL, 5LL);
    } else if (mode == 1) {
        a = rnd.next(6LL, 1000LL);
    } else if (mode == 2) {
        a = rnd.next(1001LL, 1000000000LL);
    } else if (mode == 3) {
        a = rnd.next(maxA - 1000LL, maxA);
    } else if (mode == 4) {
        a = rnd.next(1LL, maxA);
    } else {
        std::vector<long long> edgeValues = {1LL, 2LL, 3LL, 10LL, maxA - 1LL, maxA};
        a = rnd.any(edgeValues);
    }

    println(a);
    return 0;
}
