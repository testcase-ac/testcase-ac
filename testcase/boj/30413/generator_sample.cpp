#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxB = 1000000000000LL;
    int mode = rnd.next(0, 5);

    int A = 1;
    long long B = 1;

    if (mode == 0) {
        A = 1;
        B = rnd.next(1LL, maxB);
    } else if (mode == 1) {
        A = rnd.any(vector<int>{2, 3, 10, 999, 1000});
        B = rnd.next(1LL, 20LL);
    } else if (mode == 2) {
        A = rnd.next(2, 1000);
        B = rnd.next(max(1LL, maxB - 1000000LL), maxB);
    } else if (mode == 3) {
        A = rnd.any(vector<int>{2, 1000});
        B = rnd.any(vector<long long>{1LL, 2LL, 999999999LL, 1000000000LL, maxB});
    } else if (mode == 4) {
        A = rnd.next(1, 1000);
        long long base = 1LL << rnd.next(0, 39);
        B = min(maxB, base + rnd.next(0LL, 1000LL));
    } else {
        A = rnd.next(1, 1000);
        B = rnd.next(1LL, maxB);
    }

    println(A, B);
    return 0;
}
