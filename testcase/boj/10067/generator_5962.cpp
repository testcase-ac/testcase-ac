#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n small enough for manual check
    int n = rnd.next(2, 20);

    // Choose k: sometimes 1, sometimes n-1, otherwise small
    double p = rnd.next();
    int k;
    if (p < 0.2) {
        k = 1;
    } else if (p < 0.4) {
        k = n - 1;
    } else {
        k = rnd.next(1, min(n - 1, 5));
    }

    // Prepare sequence with different distribution patterns
    vector<int> a(n);
    int type = rnd.next(0, 3);
    if (type == 0) {
        // Uniform random small
        for (int i = 0; i < n; i++)
            a[i] = rnd.next(0, 10);
    } else if (type == 1) {
        // Many zeros with occasional small numbers
        for (int i = 0; i < n; i++) {
            if (rnd.next() < 0.7)
                a[i] = 0;
            else
                a[i] = rnd.next(1, 10);
        }
    } else if (type == 2) {
        // Monotonic increasing with optional noise
        int start = rnd.next(0, 5);
        int step = rnd.next(0, 5);
        for (int i = 0; i < n; i++) {
            a[i] = start + step * i;
            // small noise
            if (rnd.next() < 0.3)
                a[i] += rnd.next(0, 3);
        }
    } else {
        // One big spike among small values
        for (int i = 0; i < n; i++)
            a[i] = rnd.next(0, 5);
        int pos = rnd.next(0, n - 1);
        a[pos] = rnd.next(50, 100);
    }

    // Output
    println(n, k);
    println(a);
    return 0;
}
