#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int C = rnd.next(1, 10);
    println(C);

    vector<string> complexities = {
        "O(N)",
        "O(N^2)",
        "O(N^3)",
        "O(2^N)",
        "O(N!)"
    };

    for (int i = 0; i < C; i++) {
        // Pick a complexity
        string S = rnd.any(complexities);

        // Hyper-parameters for N based on complexity
        int N;
        if (S == "O(N)") {
            // Linear: full range
            N = rnd.next(1, 1000000);
        } else if (S == "O(N^2)") {
            // Quadratic: choose up to 20000 to allow both pass and TLE
            N = rnd.next(1, 20000);
        } else if (S == "O(N^3)") {
            // Cubic: choose up to 2000
            N = rnd.next(1, 2000);
        } else if (S == "O(2^N)") {
            // Exponential: mix small, medium, large
            double p = rnd.next();
            if (p < 0.4) {
                N = rnd.next(1, 20);
            } else if (p < 0.7) {
                N = rnd.next(21, 30);
            } else {
                N = rnd.next(31, 1000);
            }
        } else {
            // Factorial: mix small, medium, large
            double p = rnd.next();
            if (p < 0.4) {
                N = rnd.next(1, 10);
            } else if (p < 0.7) {
                N = rnd.next(11, 15);
            } else {
                N = rnd.next(16, 20);
            }
        }

        // Number of runs and time limit
        int T = rnd.next(1, 10);
        int L = rnd.next(1, 10);

        // Output the test case
        println(S, N, T, L);
    }

    return 0;
}
