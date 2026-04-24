#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int i = 0; i < T; i++) {
        // Choose C in a moderate range for clarity
        int C = rnd.next(1, 100);

        // Decide scenario for diversity
        vector<int> sc;
        // 0: N < C
        if (C > 1) sc.push_back(0);
        // 1: N divisible by C
        sc.push_back(1);
        // 2: N = k*C + r (1 <= r < C)
        if (C > 1) sc.push_back(2);
        // 3: completely random N
        sc.push_back(3);

        int scenario = rnd.any(sc);
        int N;
        if (scenario == 0) {
            // N less than C
            N = rnd.next(1, C - 1);
        } else if (scenario == 1) {
            // N divisible by C
            int k = rnd.next(1, 10);
            N = C * k;
        } else if (scenario == 2) {
            // N = k*C + r, with small remainder
            int k = rnd.next(1, 10);
            int r = rnd.next(1, C - 1);
            N = C * k + r;
        } else {
            // completely random N
            N = rnd.next(1, 1000);
        }

        // Output one test case: N C
        println(N, C);
    }

    return 0;
}
