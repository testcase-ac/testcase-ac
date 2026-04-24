#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to bias n across its range [5,100]
    vector<int> ts = {-3, -2, -1, 0, 1, 2, 3};
    int t = rnd.any(ts);
    // rnd.wnext(96, t) generates in [0,95] with bias; +5 shifts to [5,100]
    int n = 5 + rnd.wnext(96, t);

    // Choose m scenario: small (5), large (n), or random in [5,n]
    int mode = rnd.next(0, 2);
    int m;
    if (mode == 0) {
        m = 5;
    } else if (mode == 1) {
        m = n;
    } else {
        m = rnd.next(5, n);
    }

    // Output a single test: n and m
    println(n, m);
    return 0;
}
