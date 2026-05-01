#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N from a small set for hand-verifiable sizes
    vector<int> choices = {3, 5, 8, 12};
    int N = rnd.any(choices);

    // Decide on a pattern type for matrix generation
    int pattern = rnd.next(0, 3);
    vector<vector<int>> A(N, vector<int>(N, 0));

    if (pattern == 0) {
        // Fully random values in [-10,10]
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                A[i][j] = rnd.next(-10, 10);
    } else if (pattern == 1) {
        // Gradient pattern: start + dx*i + dy*j
        int start = rnd.next(-5, 5);
        int dx = rnd.next(-3, 3);
        int dy = rnd.next(-3, 3);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                A[i][j] = start + dx * i + dy * j;
    } else if (pattern == 2) {
        // Multiple rectangular blocks with constant values
        int numBlocks = rnd.next(1, 3);
        for (int b = 0; b < numBlocks; b++) {
            int r1 = rnd.next(0, N - 1);
            int r2 = rnd.next(r1, N - 1);
            int c1 = rnd.next(0, N - 1);
            int c2 = rnd.next(c1, N - 1);
            int val = rnd.next(-10, 10);
            for (int i = r1; i <= r2; i++)
                for (int j = c1; j <= c2; j++)
                    A[i][j] += val;
        }
    } else {
        // All negative values in [-10,-1]
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                A[i][j] = -rnd.next(1, 10);
    }

    // Output the test case
    println(N);
    for (int i = 0; i < N; i++)
        println(A[i]);

    return 0;
}
