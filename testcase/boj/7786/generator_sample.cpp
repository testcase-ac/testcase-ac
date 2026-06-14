#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 2000000000LL;
    long long l = 0;
    long long u = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        l = rnd.any(vector<long long>{0, 1, 9, 10, 99, 100, LIMIT});
        u = l;
    } else if (mode == 1) {
        vector<long long> centers = {
            9, 10, 11, 99, 100, 101, 999, 1000, 1001,
            9999, 10000, 99999, 100000, 999999999, 1000000000LL,
            1999999999LL, LIMIT
        };
        long long c = rnd.any(centers);
        long long width = rnd.next(0LL, 25LL);
        l = max(0LL, c - rnd.next(0LL, width));
        u = min(LIMIT, c + rnd.next(0LL, width));
    } else if (mode == 2) {
        l = rnd.next(0LL, 1000000LL);
        u = min(LIMIT, l + rnd.next(0LL, 1000000LL));
    } else if (mode == 3) {
        l = 0;
        u = rnd.next(0LL, LIMIT);
    } else if (mode == 4) {
        u = LIMIT - rnd.next(0LL, 1000000LL);
        l = max(0LL, u - rnd.next(0LL, 1000000LL));
    } else {
        l = rnd.next(0LL, LIMIT);
        u = rnd.next(l, LIMIT);
    }

    println(l, u);
    return 0;
}
