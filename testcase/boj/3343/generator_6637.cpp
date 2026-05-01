#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int sc = rnd.next(0, 4);

    long long N;
    int A, C;
    long long B, D;

    switch (sc) {
    case 0: {
        // Tiny N, small packs
        N = rnd.next(1LL, 100LL);
        A = rnd.next(1, 10);
        C = rnd.next(1, 10);
        long long maxB = min(100000LL, (long long)A * 1000LL);
        long long maxD = min(100000LL, (long long)C * 1000LL);
        B = rnd.next(1LL, maxB);
        D = rnd.next(1LL, maxD);
        break;
    }
    case 1: {
        // Medium N, moderate packs
        N = rnd.next(1000LL, 1000000000LL);
        A = rnd.next(1, 100);
        C = rnd.next(1, 100);
        long long maxB = min(100000LL, (long long)A * 500LL);
        long long maxD = min(100000LL, (long long)C * 500LL);
        B = rnd.next(1LL, maxB);
        D = rnd.next(1LL, maxD);
        break;
    }
    case 2: {
        // Large N, larger packs
        N = rnd.next(1000000000000LL, 1000000000000000LL);
        A = rnd.next(1, 1000);
        C = rnd.next(1, 1000);
        long long maxB = min(100000LL, (long long)A * 1000LL);
        long long maxD = min(100000LL, (long long)C * 1000LL);
        B = rnd.next(1LL, maxB);
        D = rnd.next(1LL, maxD);
        break;
    }
    case 3: {
        // One extremely cheap pack vs one expensive
        N = rnd.next(1LL, 1000000000000000LL);
        A = rnd.next(1, 1000);
        C = rnd.next(1, 1000);
        if (rnd.next(0, 1) == 0) {
            B = A;  // cost per rose = 1
            D = min(100000LL, (long long)C * 1000LL);
        } else {
            D = C;
            B = min(100000LL, (long long)A * 1000LL);
        }
        break;
    }
    case 4:
    default: {
        // Equal unit price
        vector<long long> ubs = {100LL, 100000000LL, 1000000000000000LL};
        long long ub = rnd.any(ubs);
        int a_ub = rnd.next(0, 1) ? 10 : 1000;
        N = rnd.next(1LL, ub);
        A = rnd.next(1, a_ub);
        C = rnd.next(1, a_ub);
        int uc = rnd.next(1, a_ub);
        B = (long long)A * uc;
        D = (long long)C * uc;
        if (B > 100000LL) B = 100000LL;
        if (D > 100000LL) D = 100000LL;
        if (B < 1LL) B = 1LL;
        if (D < 1LL) D = 1LL;
        break;
    }
    }

    println(N, A, B, C, D);
    return 0;
}
