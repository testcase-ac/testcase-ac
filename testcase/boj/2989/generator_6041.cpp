#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of leaves N between 2 and 15, skewed to smaller values
    int N = rnd.wnext(14, -1) + 2;
    // Jump cost K between 1 and 20
    int K = rnd.next(1, 20);

    // Build a monotonic path of length N
    vector<int> xs(N), ys(N), fs(N);
    int cx = rnd.next(0, 5), cy = rnd.next(0, 5);
    // Probability to move horizontally vs vertically
    double probH = rnd.next(0.0, 1.0);
    for (int i = 0; i < N; i++) {
        xs[i] = cx;
        ys[i] = cy;
        // Ensure each path node has at least K flies for viability
        fs[i] = rnd.next(K, 2 * K);
        if (i + 1 < N) {
            if (rnd.next() < probH) {
                // move horizontally
                cx += rnd.next(1, 10);
            } else {
                // move vertically
                cy += rnd.next(1, 10);
            }
        }
    }

    // Output: N K, then each leaf
    println(N, K);
    for (int i = 0; i < N; i++) {
        println(xs[i], ys[i], fs[i]);
    }
    return 0;
}
