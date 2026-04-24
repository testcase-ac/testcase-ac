#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases between 1 and 7
    int T = rnd.next(1, 7);
    println(T);
    // For biasing N selection
    vector<int> bias = {-1, 0, 1};
    for (int tc = 0; tc < T; tc++) {
        // N in [1,4], biased by wnext on [0,3]
        int delta = rnd.any(bias);
        int N = 1 + rnd.wnext(4, delta);
        int total = 1 << N;
        int R, P, S;
        // With some probability pick a trivial case (all one move)
        if (rnd.next() < 0.2) {
            int kind = rnd.next(0, 2);
            R = (kind == 0 ? total : 0);
            P = (kind == 1 ? total : 0);
            S = (kind == 2 ? total : 0);
        } else {
            // Random partition of total into R, P, S
            R = rnd.next(0, total);
            P = rnd.next(0, total - R);
            S = total - R - P;
        }
        println(N, R, P, S);
    }
    return 0;
}
