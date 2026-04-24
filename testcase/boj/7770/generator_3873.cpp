#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate a single n (1 ≤ n ≤ 1e9) with diverse distributions
    int caseType = rnd.next(0, 4);
    long long n;
    if (caseType == 0) {
        // Minimal edge case
        n = 1;
    } else if (caseType == 1) {
        // Just below a perfect pyramid size
        int k = rnd.next(2, 5);
        long long t = 1LL * k * (k + 1) * (k + 2) / 6;
        n = t - 1;
    } else if (caseType == 2) {
        // Exactly a perfect pyramid size
        int k = rnd.next(2, 5);
        n = 1LL * k * (k + 1) * (k + 2) / 6;
    } else if (caseType == 3) {
        // Small random n for hand verification
        n = rnd.next(1, 30);
    } else {
        // Large n near the upper bound
        n = 1000000000LL - rnd.next(0, 100);
    }
    println(n);
    return 0;
}
