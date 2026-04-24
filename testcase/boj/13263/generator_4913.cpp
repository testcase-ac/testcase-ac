#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for size: n in [2,10], biased small or large
    int n = rnd.wnext(9, rnd.next(-1, 1)) + 2;

    // Hyper-parameters for growth of a_i and drop of b_i
    int maxDeltaA = rnd.wnext(9, rnd.next(-1, 1)) + 1;  // in [1..9]
    int maxDeltaB = rnd.wnext(9, rnd.next(-1, 1)) + 1;  // in [1..9]

    vector<long long> a(n), b(n);
    // a_1 = 1, strictly increasing
    a[0] = 1;
    for (int i = 1; i < n; ++i) {
        int delta = rnd.next(1, maxDeltaA);
        a[i] = a[i - 1] + delta;
    }

    // b_n = 0, strictly decreasing backwards
    b[n - 1] = 0;
    for (int i = n - 2; i >= 0; --i) {
        int delta = rnd.next(1, maxDeltaB);
        b[i] = b[i + 1] + delta;
    }

    // Output
    println(n);
    println(a);
    println(b);
    return 0;
}
