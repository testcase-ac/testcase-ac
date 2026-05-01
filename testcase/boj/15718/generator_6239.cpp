#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases: small to moderate for manual verification
    int T = rnd.next(1, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        int scenario = rnd.next(1, 7);
        int N, M;
        switch (scenario) {
            case 1:
                // Edge: N=0, M=1 (only possible death immediately)
                N = 0;
                M = 1;
                break;
            case 2:
                // Edge: N=0, M small >1 (impossible except 0 ways)
                N = 0;
                M = rnd.next(2, 10);
                break;
            case 3:
                // Edge: M=1, N moderate (all eaten on day 1)
                M = 1;
                N = rnd.next(1, 1000);
                break;
            case 4:
                // Small both for trivial DP
                N = rnd.next(0, 5);
                M = rnd.next(1, 5);
                break;
            case 5:
                // Medium both
                N = rnd.next(0, 1000);
                M = rnd.next(1, 1000);
                break;
            case 6:
                // Large uniform random up to constraints
                N = rnd.next(0, 1000000000);
                M = rnd.next(1, 1000000000);
                break;
            case 7:
            default:
                // Large weighted to bias toward extremes
                N = rnd.wnext(1000000001, 1); // [0,1e9]
                M = rnd.wnext(1000000001, 1); // [0,1e9], ensure >=1
                if (M == 0) M = 1;
                break;
        }
        println(N, M);
    }
    return 0;
}
