#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of fruits
    int N = rnd.next(1, 10);
    // Maximum fruit height bound
    int Hmax = rnd.next(5, 20);
    // Initial snakebird length, can be up to Hmax+5
    int L = rnd.next(1, Hmax + 5);

    // Choose distribution type for heights
    // 0 = uniform, 1 = cluster low, 2 = cluster high
    int distType = rnd.next(0, 2);

    vector<int> h(N);
    for (int i = 0; i < N; i++) {
        if (distType == 0) {
            // uniform in [1, Hmax]
            h[i] = rnd.next(1, Hmax);
        } else if (distType == 1) {
            // cluster low: minimum of two samples in [0, Hmax-1], then +1
            h[i] = rnd.wnext(Hmax, -1) + 1;
        } else {
            // cluster high: maximum of two samples in [0, Hmax-1], then +1
            h[i] = rnd.wnext(Hmax, 1) + 1;
        }
    }

    // Shuffle input order for extra diversity
    shuffle(h.begin(), h.end());

    // Output format: N L, then heights
    println(N, L);
    println(h);

    return 0;
}
