#include "testlib.h"
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // String length hyper-parameter
    int n = rnd.next(1, 20);

    // Alphabet size hyper-parameter
    int alpha = rnd.next(1, min(12, n));
    vector<char> letters;
    for (int i = 0; i < alpha; i++) {
        letters.push_back('a' + i);
    }

    // Initialize string with placeholders
    string s(n, '?');

    // Decide whether to embed a guaranteed repeated substring
    bool hasPattern = rnd.next(0, 1) == 1;
    if (hasPattern && n >= 2) {
        // Pattern length hyper-parameter
        int patLen = rnd.next(1, n / 2);
        string pat;
        for (int i = 0; i < patLen; i++) {
            pat.push_back(rnd.any(letters));
        }
        // Place pattern at two positions (may overlap)
        int p1 = rnd.next(0, n - patLen);
        int p2 = rnd.next(0, n - patLen);
        // Ensure two distinct placements if possible
        if (p1 == p2 && n - patLen > 0) {
            p2 = (p2 + rnd.next(1, n - patLen)) % (n - patLen + 1);
        }
        for (int i = 0; i < patLen; i++) {
            s[p1 + i] = pat[i];
            s[p2 + i] = pat[i];
        }
    }

    // Fill remaining positions randomly
    for (int i = 0; i < n; i++) {
        if (s[i] == '?') {
            s[i] = rnd.any(letters);
        }
    }

    // Output the generated string
    printf("%s\n", s.c_str());
    return 0;
}
