#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter for size: sometimes small, sometimes larger up to 30
    vector<int> weight = {-3, -2, -1, 0, 1, 2, 3};
    int t = rnd.any(weight);
    int N = rnd.wnext(30, t) + 1;
    // Decide bias: with 50% chance we force a dominant grade segment
    bool biased = rnd.next(0, 1) == 0;
    int c_dom = rnd.next(1, 5);
    double p = rnd.next(30, 100) / 100.0; // fallback probability to include c_dom
    int l = 1, r = 0;
    if (biased) {
        l = rnd.next(1, N);
        int len = rnd.next(1, N - l + 1);
        r = l + len - 1;
    }
    println(N);
    for (int i = 1; i <= N; i++) {
        bool force = biased && (i >= l && i <= r);
        bool include_dom = force || (!force && rnd.next() < p);
        int A, B;
        if (include_dom) {
            // ensure at least one student has c_dom
            if (rnd.next(0, 1) == 0) {
                A = c_dom;
                B = rnd.next(1, 5);
            } else {
                A = rnd.next(1, 5);
                B = c_dom;
            }
        } else {
            A = rnd.next(1, 5);
            B = rnd.next(1, 5);
        }
        println(A, B);
    }
    return 0;
}
