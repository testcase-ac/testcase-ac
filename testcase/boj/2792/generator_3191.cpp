#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of students (N) and colors (M)
    int N = rnd.next(1, 10);
    int M = rnd.next(1, N);

    // Hyper-parameter: maximum count per color
    vector<int> caps = {5, 10, 20, 50};
    int Cmax = rnd.any(caps);

    // Generate counts with some skew: uniform or weighted extremes
    vector<int> a(M);
    for (int i = 0; i < M; i++) {
        // decide uniform or weighted
        if (rnd.next(0, 1) == 0) {
            // uniform in [1, Cmax]
            a[i] = rnd.next(1, Cmax);
        } else {
            // weighted towards lows or highs
            int t = rnd.next(-2, 2);  // t<0 -> min, t>0 -> max, t=0 -> uniform
            a[i] = rnd.wnext(Cmax, t) + 1;  // wnext gives [0, Cmax-1]
        }
    }

    // Output
    println(N, M);
    for (int x : a) println(x);

    return 0;
}
