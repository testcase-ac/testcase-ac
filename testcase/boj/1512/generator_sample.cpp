#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomDna(const string& alphabet) {
    return alphabet[rnd.next((int)alphabet.size())];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string dna = "ACGT";
    int mode = rnd.next(6);
    int n;
    int m;
    string s;

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1, n);
        string alphabet = dna.substr(0, rnd.next(1, 4));
        for (int i = 0; i < n; ++i) s += randomDna(alphabet);
    } else if (mode == 1) {
        n = rnd.next(8, 40);
        int period = rnd.next(1, min(8, n));
        m = rnd.next(period, n);
        string pattern;
        for (int i = 0; i < period; ++i) pattern += randomDna(dna);
        for (int i = 0; i < n; ++i) s += pattern[i % period];
    } else if (mode == 2) {
        n = rnd.next(12, 60);
        int period = rnd.next(1, min(10, n));
        m = rnd.next(period, n);
        string pattern;
        for (int i = 0; i < period; ++i) pattern += randomDna(dna);
        for (int i = 0; i < n; ++i) s += pattern[i % period];

        int changes = rnd.next(1, min(12, n));
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(n);
            char next = randomDna(dna);
            while (next == s[pos]) next = randomDna(dna);
            s[pos] = next;
        }
    } else if (mode == 3) {
        n = rnd.next(10, 70);
        m = rnd.next(1, min(5, n));
        string alphabet = dna.substr(0, rnd.next(2, 4));
        for (int i = 0; i < n; ++i) s += randomDna(alphabet);
    } else if (mode == 4) {
        n = rnd.next(15, 90);
        m = rnd.next(max(1, n - 8), n);
        for (int i = 0; i < n; ++i) s += randomDna(dna);
    } else {
        n = rnd.next(50, 160);
        int period = rnd.next(2, 13);
        m = rnd.next(1, min(n, period + rnd.next(0, 6)));
        string pattern;
        for (int i = 0; i < period; ++i) pattern += randomDna(dna);
        for (int i = 0; i < n; ++i) s += pattern[i % period];

        int changes = rnd.next(0, min(20, n));
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(n);
            s[pos] = randomDna(dna);
        }
    }

    println(m);
    println(s);

    return 0;
}
