/* generator code */
#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of file names and their length
    int N = rnd.next(1, 10);
    int L = rnd.next(1, 10);

    // Alphabet: lowercase letters and dot
    string alph = "abcdefghijklmnopqrstuvwxyz.";

    // Generate a base name
    string base;
    base.reserve(L);
    for (int j = 0; j < L; j++) {
        base.push_back(rnd.any(alph));
    }

    // Decide which positions will vary
    vector<bool> var(L, false);
    double varProb = rnd.next(0.0, 1.0);
    for (int j = 0; j < L; j++) {
        var[j] = (rnd.next() < varProb);
    }
    // If more than one name and no variation so far, force at least one
    if (N > 1) {
        bool anyVar = false;
        for (bool b : var) if (b) { anyVar = true; break; }
        if (!anyVar) {
            int j = rnd.next(0, L - 1);
            var[j] = true;
        }
    }

    // Build the list of file names
    vector<string> names(N, string(L, ' '));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++) {
            if (N == 1 || !var[j]) {
                // Position is fixed
                names[i][j] = base[j];
            } else {
                // Position varies: keep first string = base, others != base
                if (i == 0) {
                    names[i][j] = base[j];
                } else {
                    char c;
                    do {
                        c = rnd.any(alph);
                    } while (c == base[j]);
                    names[i][j] = c;
                }
            }
        }
    }

    // Output
    println(N);
    for (auto &s : names) {
        println(s);
    }
    return 0;
}
