#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; tc++) {
        // Length of string S
        int N = rnd.next(2, 10);
        string S;
        double p = rnd.next();
        if (p < 0.4) {
            // Completely random string
            for (int i = 0; i < N; i++) {
                S.push_back(char(rnd.next(97, 126)));
            }
        }
        else if (p < 0.8) {
            // Fully periodic over the entire string
            // Find divisors d of N with d <= N/2
            vector<int> divs;
            for (int d = 1; d <= N/2; d++) {
                if (N % d == 0) divs.push_back(d);
            }
            if (divs.empty()) {
                // Fallback to random
                for (int i = 0; i < N; i++)
                    S.push_back(char(rnd.next(97, 126)));
            } else {
                int d = rnd.any(divs);
                string A;
                for (int i = 0; i < d; i++)
                    A.push_back(char(rnd.next(97, 126)));
                // Repeat A to fill S
                for (int i = 0; i < N/d; i++)
                    S += A;
            }
        }
        else {
            // Partially periodic: one prefix is periodic, the rest random
            if (N < 5) {
                // Not enough length, fallback to random
                for (int i = 0; i < N; i++)
                    S.push_back(char(rnd.next(97, 126)));
            } else {
                // Choose a prefix length P >= 4 to have nontrivial period
                int P = rnd.next(4, N-1);
                // Find divisors d of P with P/d >= 2 (i.e. d <= P/2)
                vector<int> divsP;
                for (int d = 1; d <= P/2; d++) {
                    if (P % d == 0) divsP.push_back(d);
                }
                if (divsP.empty()) {
                    // Fallback random
                    for (int i = 0; i < N; i++)
                        S.push_back(char(rnd.next(97, 126)));
                } else {
                    int d = rnd.any(divsP);
                    string A;
                    for (int i = 0; i < d; i++)
                        A.push_back(char(rnd.next(97, 126)));
                    // Build the periodic prefix of length P
                    for (int i = 0; i < P/d; i++)
                        S += A;
                    // If P is not a multiple of d (shouldn't happen), fill rem
                    while ((int)S.size() < P)
                        S.push_back(A[S.size() % d]);
                    // Fill the rest randomly
                    for (int i = P; i < N; i++)
                        S.push_back(char(rnd.next(97, 126)));
                }
            }
        }
        // Output this test case
        println(N);
        println(S);
    }
    // End marker
    println(0);
    return 0;
}
