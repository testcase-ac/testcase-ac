#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose string length between 1 and 10
    int n = rnd.next(1, 10);
    double r = rnd.next();

    string S;
    S.resize(n);

    if (r < 0.15) {
        // All characters the same
        char c = char('A' + rnd.next(0, 25));
        for (int i = 0; i < n; i++) S[i] = c;
    } else if (r < 0.40) {
        // Pure periodic pattern
        int p = rnd.next(1, n);
        int a = rnd.next(1, min(5, n));
        vector<char> alph(a);
        for (int i = 0; i < a; i++) alph[i] = char('A' + i);
        vector<char> base(p);
        for (int i = 0; i < p; i++) base[i] = alph[rnd.next(0, a - 1)];
        for (int i = 0; i < n; i++) S[i] = base[i % p];
    } else if (r < 0.60) {
        // Periodic with small noise
        int p = rnd.next(1, n);
        int a = rnd.next(1, min(5, n));
        vector<char> alph(a);
        for (int i = 0; i < a; i++) alph[i] = char('A' + i);
        vector<char> base(p);
        for (int i = 0; i < p; i++) base[i] = alph[rnd.next(0, a - 1)];
        for (int i = 0; i < n; i++) {
            char c = base[i % p];
            if (rnd.next() < 0.2) c = alph[rnd.next(0, a - 1)];
            S[i] = c;
        }
    } else if (r < 0.80) {
        // Random with small alphabet
        int a = rnd.next(1, min(3, n));
        vector<char> alph(a);
        for (int i = 0; i < a; i++) alph[i] = char('A' + i);
        for (int i = 0; i < n; i++) S[i] = alph[rnd.next(0, a - 1)];
    } else {
        // Fully random uppercase string
        for (int i = 0; i < n; i++) S[i] = char('A' + rnd.next(0, 25));
    }

    // Output the generated string
    printf("%s\n", S.c_str());
    return 0;
}
