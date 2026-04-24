#include "testlib.h"
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);
    int W = rnd.next(1, 20);
    int H = rnd.next(1, 20);
    double diag = sqrt(1.0 * W * W + 1.0 * H * H);
    int a = min(W, H);
    int b = max(W, H);
    int c = int(floor(diag));

    // Output header
    println(N, W, H);
    // Generate match lengths in several categories
    for (int i = 0; i < N; i++) {
        double u = rnd.next();
        int len;
        if (u < 0.2) {
            // Definitely fits by one side
            if (a >= 1) len = rnd.next(1, a);
            else len = 1;
        } else if (u < 0.4) {
            // Fits by the other side
            if (b >= a + 1) len = rnd.next(a + 1, b);
            else len = rnd.next(1, max(1, a));
        } else if (u < 0.7) {
            // Fits only by diagonal
            if (c >= b + 1) len = rnd.next(b + 1, c);
            else len = rnd.next(1, max(b, c));
        } else if (u < 0.9) {
            // Just slightly too long for diagonal
            len = rnd.next(c + 1, c + 5);
        } else {
            // Clearly too long
            int high = max(c + 6, c + 20);
            len = rnd.next(c + 6, high);
        }
        // Cap by problem constraint
        if (len > 1000) len = 1000;
        println(len);
    }
    return 0;
}
