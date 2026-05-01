#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(2, 4);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        // Choose N with skew towards small values, max 10 for compactness
        double pN = rnd.next();
        int N;
        if (pN < 0.1) N = 1;
        else if (pN < 0.5) N = rnd.next(2, 3);
        else if (pN < 0.8) N = rnd.next(4, 7);
        else N = rnd.next(8, 10);
        println(N);

        // Hyper-parameter for speed distribution
        int spType = rnd.next(0, 3);
        vector<long long> S(N);
        for (int i = 0; i < N; i++) {
            if (spType == 0) {
                S[i] = 0;
            } else if (spType == 1) {
                S[i] = rnd.next(1, 10);
            } else if (spType == 2) {
                S[i] = rnd.next(100000000, 1000000000);
            } else {
                S[i] = rnd.next(0, 1000000000);
            }
        }
        println(S);

        // Hyper-parameter for direction patterns
        double pat = rnd.next();
        vector<char> C(N);
        if (pat < 0.1) {
            // All towards
            for (int i = 0; i < N; i++) C[i] = 'T';
        } else if (pat < 0.2) {
            // All away
            for (int i = 0; i < N; i++) C[i] = 'A';
        } else if (pat < 0.35) {
            // Alternating starting with T
            for (int i = 0; i < N; i++) C[i] = (i % 2 == 0 ? 'T' : 'A');
        } else if (pat < 0.5) {
            // Alternating starting with A
            for (int i = 0; i < N; i++) C[i] = (i % 2 == 0 ? 'A' : 'T');
        } else {
            // Random with bias
            double pT = rnd.next(0.0, 1.0);
            for (int i = 0; i < N; i++) {
                C[i] = (rnd.next() < pT ? 'T' : 'A');
            }
        }
        // Build and print direction line
        string dir_line;
        for (int i = 0; i < N; i++) {
            dir_line += C[i];
            if (i + 1 < N) dir_line += ' ';
        }
        println(dir_line);
    }

    return 0;
}
