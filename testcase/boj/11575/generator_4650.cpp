#include "testlib.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Precompute 'a' values coprime with 26 (1..100)
    vector<int> coprimeA;
    for (int a = 1; a <= 100; ++a) {
        if (gcd(a, 26) == 1)
            coprimeA.push_back(a);
    }

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Choose a and b
        int a = rnd.any(coprimeA);
        int b;
        if (rnd.next(0, 1) == 0) {
            // small b to test simple shifts
            b = rnd.next(1, 25);
        } else {
            // larger b to test mod behavior
            b = rnd.next(26, 1000000);
        }
        println(a, b);

        // Plain‐text length
        int L = rnd.next(1, 20);

        // Generate plaintext with varied patterns
        string s;
        int pat = rnd.next(0, 4);
        switch (pat) {
            case 0:
                // fully random
                for (int i = 0; i < L; ++i)
                    s.push_back(char(rnd.next('A', 'Z')));
                break;
            case 1:
                // repeated single letter
                {
                    char c = char(rnd.next('A', 'Z'));
                    s = string(L, c);
                }
                break;
            case 2:
                // alphabetical wrap-around sequence
                for (int i = 0; i < L; ++i)
                    s.push_back(char('A' + (i % 26)));
                break;
            case 3:
                // palindrome
                {
                    int half = (L + 1) / 2;
                    for (int i = 0; i < half; ++i)
                        s.push_back(char(rnd.next('A', 'Z')));
                    int start = (L % 2 ? half - 2 : half - 1);
                    for (int i = start; i >= 0; --i)
                        s.push_back(s[i]);
                }
                break;
            case 4:
                // alternating two letters
                {
                    char c1 = char(rnd.next('A', 'Z'));
                    char c2 = char(rnd.next('A', 'Z'));
                    for (int i = 0; i < L; ++i)
                        s.push_back(i % 2 ? c2 : c1);
                }
                break;
        }

        // Output the plaintext
        printf("%s\n", s.c_str());
    }

    return 0;
}
