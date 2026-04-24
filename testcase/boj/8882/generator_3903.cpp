#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n, k such that 2*n*k is small (<=20)
    int n, k;
    do {
        n = rnd.next(1, 3);
        k = rnd.next(1, 4);
    } while (2LL * n * k > 20);
    int m = 2 * n * k;

    // Hyper-parameter: choose a max power range
    vector<int> ranges = {5, 10, 20, 50, 100};
    int R = rnd.any(ranges);

    // Hyper-parameter: bias for distribution of battery powers
    int t = rnd.next(-2, 2);

    // Generate battery powers with possible bias
    vector<int> p(m);
    for (int i = 0; i < m; i++) {
        // rnd.wnext(R, t) gives [0, R-1] with bias; +1 shifts to [1, R]
        p[i] = 1 + rnd.wnext(R, t);
    }

    // Shuffle to randomize order
    shuffle(p.begin(), p.end());

    // Output
    println(n, k);
    println(p);

    return 0;
}
