#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for n and m
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 20);

    // Decide if all a_i are the same or varied
    bool commonA = rnd.next() < 0.3;
    int commonValue = rnd.next(1, 50);

    // Rate at which b_i will be zero
    double biZeroRate = rnd.next();

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        // Generate a_i
        if (commonA) {
            a[i] = commonValue;
        } else {
            a[i] = rnd.next(1, 50);
        }
        // Generate b_i
        if (rnd.next() < biZeroRate) {
            b[i] = 0;
        } else {
            b[i] = rnd.next(1, a[i]);
        }
    }

    // Output
    println(n, m);
    println(a);
    println(b);

    return 0;
}
