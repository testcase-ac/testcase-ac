#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: length of sequence
    int n = rnd.next(1, 10);
    vector<int> a(n);

    // Mode selector: 0 = strictly non-decreasing, 1 = one violation, 2 = random, 3 = constant
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        // Good: non-decreasing
        a[0] = rnd.next(-10, 10);
        for (int i = 1; i < n; i++) {
            a[i] = a[i-1] + rnd.next(0, 5);
        }
    } else if (mode == 1) {
        // Bad: introduce a single violation
        a[0] = rnd.next(-10, 10);
        for (int i = 1; i < n; i++) {
            a[i] = a[i-1] + rnd.next(0, 5);
        }
        if (n >= 2) {
            int pos = rnd.next(1, n-1);
            int left = a[pos-1];
            // Make a[pos] less than a[pos-1]
            a[pos] = rnd.next(left - 5, left - 1);
            // After the violation, continue non-decreasing to keep it subtle
            for (int i = pos+1; i < n; i++) {
                a[i] = a[i-1] + rnd.next(0, 5);
            }
        }
    } else if (mode == 2) {
        // Random sequence
        for (int i = 0; i < n; i++) {
            a[i] = rnd.next(-10, 10);
        }
    } else {
        // Constant sequence: Good
        int v = rnd.next(-10, 10);
        for (int i = 0; i < n; i++) {
            a[i] = v;
        }
    }

    // Output the sequence (space-separated on one line)
    println(a);

    return 0;
}
