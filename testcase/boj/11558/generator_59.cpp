#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

// Constants for random variables
const int MIN_T = 1;
const int MAX_T = 2;

const int MIN_N = 2;
const int MAX_N = 8;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate T test cases
    int T = rnd.next(MIN_T, MAX_T);
    printf("%d\n", T);

    for(int testCase = 0; testCase < T; testCase++) {
        // Randomly select N
        int N = rnd.next(MIN_N, MAX_N);
        printf("%d\n", N);

        // Randomly select type of test case
        int type = rnd.next(1,4);

        vector<int> A(N+1); // 1-indexed

        if(type == 1) {
            // Type 1: Linear chain
            for(int i = 1; i <= N; i++) {
                A[i] = i % N + 1;
            }
        } else if(type == 2) {
            // Type 2: Random pointing
            for(int i = 1; i <= N; i++) {
                A[i] = rnd.next(1,N);
            }
        } else if(type == 3) {
            // Type 3: Self-pointing
            for(int i = 1; i <= N; i++) {
                A[i] = i;
            }
        } else if(type == 4) {
            // Type 4: Star pattern, everyone points to a single random player
            int target = rnd.next(1,N);
            for(int i = 1; i <= N; i++) {
                A[i] = target;
            }
        }

        // Output Ai's
        for(int i = 1; i <= N; i++) {
            printf("%d\n", A[i]);
        }
    }

    return 0;
}
