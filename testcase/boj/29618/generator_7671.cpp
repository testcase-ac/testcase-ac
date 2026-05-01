#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cells and queries
    int N = rnd.next(1, 15);
    int Q = rnd.next(1, 30);
    println(N, Q);
    // Generate queries with diverse interval lengths and color values
    for (int i = 0; i < Q; ++i) {
        // Decide on interval length: bias towards short or long
        int len;
        if (rnd.next() < 0.3) {
            // longer intervals
            len = rnd.wnext(N, 2) + 1;
        } else {
            // shorter intervals
            len = rnd.wnext(N, -2) + 1;
        }
        len = min(len, N);
        // Choose start and end within [1, N]
        int a = rnd.next(1, N - len + 1);
        int b = a + len - 1;
        // Choose color: mostly small, sometimes very large
        int x;
        if (rnd.next() < 0.7) {
            x = rnd.next(1, 10);
        } else {
            x = rnd.next(1000000000 - 10, 1000000000);
        }
        println(a, b, x);
    }
    return 0;
}
