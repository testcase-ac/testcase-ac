#include "testlib.h"
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    int n = rnd.next(1, 30);                // length of S
    double digitProb = rnd.next();          // probability of digit in S
    double upperProb = rnd.next();          // probability of uppercase letter
    bool exist = rnd.next(0, 1);            // whether K should exist in S
    int klen = rnd.next(1, n);              // length of K

    const string digits = "0123456789";
    const string lowers = "abcdefghijklmnopqrstuvwxyz";
    const string uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Generate K (letters only)
    string K;
    K.reserve(klen);
    for (int i = 0; i < klen; i++) {
        if (rnd.next() < upperProb)
            K.push_back(rnd.any(uppers));
        else
            K.push_back(rnd.any(lowers));
    }

    // Function to generate a random character (digit or letter)
    auto genChar = [&]() {
        if (rnd.next() < digitProb) {
            return rnd.any(digits);
        } else {
            if (rnd.next() < upperProb) return rnd.any(uppers);
            else return rnd.any(lowers);
        }
    };

    string S;
    S.resize(n);
    if (exist) {
        // Embed K at a random position
        int pos = rnd.next(0, n - klen);
        // before
        for (int i = 0; i < pos; i++) S[i] = genChar();
        // K
        for (int i = 0; i < klen; i++) S[pos + i] = K[i];
        // after
        for (int i = pos + klen; i < n; i++) S[i] = genChar();
    } else {
        // Ensure K does NOT appear in S
        if (klen == 1) {
            char ban = K[0];
            for (int i = 0; i < n; i++) {
                char c;
                do { c = genChar(); } while (c == ban);
                S[i] = c;
            }
        } else {
            // retry until no substring
            do {
                for (int i = 0; i < n; i++) S[i] = genChar();
            } while (S.find(K) != string::npos);
        }
    }

    // Output
    printf("%s\n", S.c_str());
    printf("%s\n", K.c_str());
    return 0;
}
