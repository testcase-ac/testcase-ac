/* generator code */
#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small grid dimensions
    int n = rnd.next(2, 10);
    int m = rnd.next(2, 10);
    // Number of cuts
    int r = rnd.next(1, n - 1);
    int s = rnd.next(1, m - 1);

    // Output header
    println(n, m, r, s);

    // Generate grid with small values, mixing uniform and biased distributions
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            // 50% chance uniform, 50% weighted towards higher values
            if (rnd.next(0, 1) == 0) {
                x = rnd.next(0, 10);
            } else {
                x = rnd.wnext(10, 3);
            }
            // Print with spaces
            printf("%d", x);
            if (j + 1 < m) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
