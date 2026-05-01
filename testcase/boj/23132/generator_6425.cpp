#include "testlib.h"
#include <cstdint>
#include <vector>
using namespace std;
using ull = unsigned long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose K between 6 and 15
    int K = rnd.next(6, 15);

    // Choose m: sometimes small (<K), equal K, modestly above, or very large
    ull m;
    double p = rnd.next();  // [0,1)
    if (p < 0.2) {
        // m in [1, K-1]
        m = rnd.next((ull)1, (ull)(K - 1));
    } else if (p < 0.3) {
        // m = K
        m = (ull)K;
    } else if (p < 0.6) {
        // m modestly larger than K
        m = rnd.next((ull)(K + 1), (ull)(K + 100));
    } else {
        // m large, up to 1e18
        m = rnd.next((ull)100, (ull)1000000000000000000ULL);
    }

    // Generate initial a[1..K-1] with 3 distribution modes
    vector<ull> a(K - 1);
    int modeA = rnd.next(0, 2);
    for (int i = 0; i < K - 1; i++) {
        if (modeA == 0) {
            // small values
            a[i] = rnd.next((ull)0, (ull)100);
        } else if (modeA == 1) {
            // full 32-bit range
            a[i] = rnd.next((ull)0, (ull)0xFFFFFFFFULL);
        } else {
            // sparse single-bit
            int bit = rnd.next(0, 31);
            a[i] = 1ULL << bit;
        }
    }

    // Generate b[1..5] and c[1..5] similarly
    vector<ull> b(5), c(5);
    int modeB = rnd.next(0, 2), modeC = rnd.next(0, 2);
    for (int i = 0; i < 5; i++) {
        if (modeB == 0) {
            b[i] = rnd.next((ull)0, (ull)100);
        } else if (modeB == 1) {
            b[i] = rnd.next((ull)0, (ull)0xFFFFFFFFULL);
        } else {
            int bit = rnd.next(0, 31);
            b[i] = 1ULL << bit;
        }
        if (modeC == 0) {
            c[i] = rnd.next((ull)0, (ull)100);
        } else if (modeC == 1) {
            c[i] = rnd.next((ull)0, (ull)0xFFFFFFFFULL);
        } else {
            int bit = rnd.next(0, 31);
            c[i] = 1ULL << bit;
        }
    }

    // Occasionally zero out all of b or all of c to test edge cases
    if (rnd.next(0, 9) == 0) {
        for (int i = 0; i < 5; i++) b[i] = 0;
    }
    if (rnd.next(0, 9) == 0) {
        for (int i = 0; i < 5; i++) c[i] = 0;
    }

    // Output the generated test case
    println(K, m);
    println(a);
    println(b);
    println(c);

    return 0;
}
