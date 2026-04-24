#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; tc++) {
        // Length of the sequence
        int n = rnd.next(2, 10);
        println(n);

        // Choose a pattern type for diversity
        // 0: random with bias p
        // 1: all ones
        // 2: all twos
        // 3: alternating starting with 1 or 2
        int type = rnd.next(0, 3);
        double p = rnd.next(0.0, 1.0);

        vector<int> a(n);
        if (type == 1) {
            // All ones
            for (int i = 0; i < n; i++)
                a[i] = 1;
        } else if (type == 2) {
            // All twos
            for (int i = 0; i < n; i++)
                a[i] = 2;
        } else if (type == 3) {
            // Alternating pattern
            int start = rnd.next(1, 2);
            int other = (start == 1 ? 2 : 1);
            for (int i = 0; i < n; i++)
                a[i] = (i % 2 == 0 ? start : other);
        } else {
            // Random with probability p for 2
            for (int i = 0; i < n; i++)
                a[i] = (rnd.next() < p ? 2 : 1);
        }

        // Output the sequence
        println(a);
    }

    return 0;
}
