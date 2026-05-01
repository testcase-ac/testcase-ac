#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter t for biasing n
    int t_n = rnd.next(-3, 3);
    int n = rnd.wnext(20, t_n) + 1; // n in [1,20], biased

    // Hyper-parameter t for biasing w
    int hiW = min(20, max(1, n * 2));
    int t_w = rnd.next(-2, 2);
    int w = rnd.wnext(hiW, t_w) + 1; // w in [1, hiW]

    // Build truck weights with a heavy probability
    double heavyProb = rnd.next(); // in [0,1)
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (rnd.next() < heavyProb) {
            a[i] = rnd.next(8, 10);
        } else {
            a[i] = rnd.next(1, 7);
        }
    }

    // Occasionally create a contiguous heavy block
    if (n > 3 && rnd.next() < 0.3) {
        int len = rnd.next(2, min(n, 5));
        int start = rnd.next(0, n - len);
        for (int i = start; i < start + len; i++)
            a[i] = rnd.next(8, 10);
    }

    int sumA = accumulate(a.begin(), a.end(), 0);
    int maxA = *max_element(a.begin(), a.end());
    int Lmin = max(maxA, 10);
    int Lmax = min(1000, sumA * 2);
    if (Lmin > Lmax) Lmax = Lmin;
    int L = rnd.next(Lmin, Lmax);

    // Output the test case
    println(n, w, L);
    println(a);

    return 0;
}
