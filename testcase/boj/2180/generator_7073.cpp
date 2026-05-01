#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Decide n: sometimes 1, else [2..20] with bias
    int n;
    if (rnd.next() < 0.1) {
        n = 1;
    } else {
        int t = rnd.next(-3, 3);
        n = rnd.wnext(19, t) + 2; // in [2..20]
    }
    // Hyper-parameters for value distributions
    double high_a_p = rnd.next(0.0, 1.0);
    double high_b_p = rnd.next(0.0, 1.0);
    bool force_zero_a = rnd.next(0.0, 1.0) < 0.5;
    bool force_zero_b = rnd.next(0.0, 1.0) < 0.5;

    vector<pair<int,int>> v(n);
    // Generate (a, b)
    for (int i = 0; i < n; i++) {
        int a = (rnd.next() < high_a_p
                 ? rnd.next(10000, 40000)
                 : rnd.next(0, 9999));
        int b = (rnd.next() < high_b_p
                 ? rnd.next(10000, 40000)
                 : rnd.next(0, 9999));
        v[i] = {a, b};
    }
    // Ensure at least one zero a or b if flagged
    if (force_zero_a && n > 0) {
        int idx = rnd.next(0, n - 1);
        v[idx].first = 0;
    }
    if (force_zero_b && n > 0) {
        int idx = rnd.next(0, n - 1);
        v[idx].second = 0;
    }
    // Also ensure we have some max values to test extremes
    if (n >= 2) {
        v[0].first = 40000;
        v[1].second = 40000;
    }

    // Output
    println(n);
    for (auto &p : v) {
        println(p.first, p.second);
    }
    return 0;
}
