#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for sizes
    int N = rnd.next(1, 10);
    int m = rnd.next(1, min(N, 5));

    // Alphabet
    vector<char> alpha = {'R','I','N','G','S'};

    // Generate pattern string with different structures
    string pattern;
    int patMode = rnd.next(0, 2);
    if (patMode == 0) {
        // Unique characters (only if m <= 5)
        vector<char> tmp = alpha;
        shuffle(tmp.begin(), tmp.end());
        for (int i = 0; i < m; i++) pattern.push_back(tmp[i]);
    } else if (patMode == 1) {
        // Repeated same character
        char c = rnd.any(alpha);
        pattern = string(m, c);
    } else {
        // Completely random
        for (int i = 0; i < m; i++) pattern.push_back(rnd.any(alpha));
    }

    // Distribution mode for bridge characters
    int distMode = rnd.next(0, 2);
    char biasChar = 0;
    if (distMode == 1) {
        biasChar = rnd.any(alpha);
    }

    // Correlation mode between the two bridges
    int corrMode = rnd.next(0, 2);

    // Generate two bridge strings
    string A(N, ' '), B(N, ' ');
    for (int i = 0; i < N; i++) {
        // Generate A[i]
        if (distMode == 0) {
            A[i] = rnd.any(alpha);
        } else if (distMode == 1) {
            if (rnd.next() < 0.5) A[i] = biasChar;
            else A[i] = rnd.any(alpha);
        } else {
            // pure random (same as mode 0, but we keep for clarity)
            A[i] = rnd.any(alpha);
        }
    }

    for (int i = 0; i < N; i++) {
        if (corrMode == 0) {
            // independent
            if (distMode == 0) {
                B[i] = rnd.any(alpha);
            } else if (distMode == 1) {
                if (rnd.next() < 0.5) B[i] = biasChar;
                else B[i] = rnd.any(alpha);
            } else {
                B[i] = rnd.any(alpha);
            }
        } else if (corrMode == 1) {
            // identical
            B[i] = A[i];
        } else {
            // different
            char c;
            do {
                c = rnd.any(alpha);
            } while (c == A[i]);
            B[i] = c;
        }
    }

    // Output: pattern, then two bridges
    printf("%s\n", pattern.c_str());
    printf("%s\n", A.c_str());
    printf("%s\n", B.c_str());

    return 0;
}
