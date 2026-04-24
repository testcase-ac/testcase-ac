#include "testlib.h"
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for n: bias low, bias high, or uniform
    double p = rnd.next();
    int n;
    if (p < 0.3) {
        // bias towards small n in [1,10]
        n = rnd.wnext(10, -1) + 1;
    } else if (p < 0.6) {
        // bias towards large n in [1,10]
        n = rnd.wnext(10, 1) + 1;
    } else {
        // uniform n in [1,10]
        n = rnd.next(1, 10);
    }

    // Compute the size of R(n): 0/1 plus all a/d with 1 <= a <= d <= n and gcd(a,d)=1
    int total = 1; // count 0/1
    for (int d = 1; d <= n; d++) {
        int cnt = 0;
        for (int a = 1; a <= d; a++) {
            if (std::gcd(a, d) == 1) cnt++;
        }
        total += cnt;
    }

    // Hyper-parameter for k: bias low, uniform, or bias high
    double q = rnd.next();
    int k;
    if (q < 0.33) {
        // bias towards small k
        k = rnd.wnext(total, -1) + 1;
    } else if (q < 0.66) {
        // uniform k in [1,total]
        k = rnd.next(1, total);
    } else {
        // bias towards large k
        k = rnd.wnext(total, 1) + 1;
    }

    // Output the test case
    println(n, k);

    return 0;
}
