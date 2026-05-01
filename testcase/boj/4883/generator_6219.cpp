#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(3, 6);
    for (int tc = 0; tc < T; tc++) {
        // Generate N in [2,10], biased by wnext
        int weight = rnd.next(-2, 2);
        int N = rnd.wnext(9, weight) + 2;
        // Mode for cost pattern: 0=random, 1=increasing, 2=decreasing
        int mode = rnd.next(0, 2);
        println(N);
        for (int i = 0; i < N; i++) {
            int base = 0;
            if (mode == 1) base = i * 3;
            else if (mode == 2) base = (N - 1 - i) * 3;
            int mx = (mode == 0 ? 99 : 5);
            int c1 = base + rnd.next(0, mx);
            int c2 = base + rnd.next(0, mx);
            int c3 = base + rnd.next(0, mx);
            println(c1, c2, c3);
        }
    }
    // End of all test cases
    println(0);
    return 0;
}
