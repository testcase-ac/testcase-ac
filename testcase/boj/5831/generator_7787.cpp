#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sample N: small, medium, or large
    int sizeCat = rnd.next(0, 2);
    int N;
    if (sizeCat == 0) N = rnd.next(3, 5);
    else if (sizeCat == 1) N = rnd.next(6, 10);
    else N = rnd.next(11, 16);
    // Sample B with diverse categories
    const long long MAXB = 1000000000000000LL;        // 1e15
    const long long LARGE_LO = 100000000000000LL;     // 1e14
    long long B;
    int bCat = rnd.next(0, 4);
    if (bCat == 0) {
        B = 1;                                        // minimal
    } else if (bCat == 1) {
        B = rnd.next(1LL, (long long)(2 * N));       // small
    } else if (bCat == 2) {
        int e = rnd.next(0, 49);                      // power of two
        B = 1LL << e;
    } else if (bCat == 3) {
        B = rnd.next(LARGE_LO, MAXB - 1);             // large random
    } else {
        B = MAXB;                                     // maximal
    }
    // Generate initial state patterns
    int a[16];
    int p = rnd.next(0, 6);
    if (p == 0) {
        for (int i = 0; i < N; ++i) a[i] = 0;          // all off
    } else if (p == 1) {
        for (int i = 0; i < N; ++i) a[i] = 1;          // all on
    } else if (p == 2) {
        for (int i = 0; i < N; ++i) a[i] = (i % 2);    // 0101...
    } else if (p == 3) {
        for (int i = 0; i < N; ++i) a[i] = 1 - (i % 2);// 1010...
    } else if (p == 4) {
        for (int i = 0; i < N; ++i) a[i] = 0;
        a[rnd.next(0, N - 1)] = 1;                    // single on
    } else if (p == 5) {
        for (int i = 0; i < N; ++i) a[i] = 1;
        a[rnd.next(0, N - 1)] = 0;                    // single off
    } else {
        for (int i = 0; i < N; ++i) a[i] = rnd.next(0, 1); // random
    }
    // Output
    println(N, B);
    for (int i = 0; i < N; ++i) println(a[i]);
    return 0;
}
