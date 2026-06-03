#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_N = 3;
    const long long MAX_N = 1000000000LL;
    const long long MIN_A = 1;
    const long long MAX_A = 1000000000LL;

    int mode = rnd.next(0, 5);
    long long n;
    long long a;

    if (mode == 0) {
        n = rnd.next(MIN_N, 12LL);
        a = rnd.next(MIN_A, 12LL);
    } else if (mode == 1) {
        vector<long long> commonN = {3, 4, 5, 6, 8, 10, 12, 20, 100};
        n = rnd.any(commonN);
        a = rnd.next(MIN_A, 1000LL);
    } else if (mode == 2) {
        n = rnd.next(MAX_N - 100000LL, MAX_N);
        a = rnd.next(MIN_A, 1000000LL);
    } else if (mode == 3) {
        n = rnd.next(MIN_N, 1000000LL);
        a = rnd.next(MAX_A - 100000LL, MAX_A);
    } else if (mode == 4) {
        vector<long long> specialN = {3, 4, 5, 10, 1000000000LL, 999999937LL};
        vector<long long> specialA = {1, 2, 3, 10, 999999937LL, 1000000000LL};
        n = rnd.any(specialN);
        a = rnd.any(specialA);
    } else {
        n = rnd.next(MIN_N, MAX_N);
        a = rnd.next(MIN_A, MAX_A);
    }

    println(n, a);
    return 0;
}
