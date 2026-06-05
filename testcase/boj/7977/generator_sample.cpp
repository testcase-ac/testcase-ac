#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomDna(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string bases = "ACGT";
    int mode = rnd.next(0, 8);
    int n;
    string dna;

    if (mode == 0) {
        n = rnd.next(1, 6);
        dna = randomDna(n, bases);
    } else if (mode == 1) {
        n = rnd.next(1, 40);
        dna.assign(n, rnd.any(bases));
    } else if (mode == 2) {
        n = rnd.next(2, 80);
        string alphabet = bases;
        shuffle(alphabet.begin(), alphabet.end());
        alphabet.resize(2);
        dna = randomDna(n, alphabet);
    } else if (mode == 3) {
        n = rnd.next(4, 120);
        vector<int> counts(4, 0);
        int remaining = n;
        for (int i = 0; i < 3; ++i) {
            int take = rnd.next(0, remaining);
            counts[i] = take;
            remaining -= take;
        }
        counts[3] = remaining;
        shuffle(counts.begin(), counts.end());
        for (int i = 0; i < 4; ++i) dna.append(counts[i], bases[i]);
    } else if (mode == 4) {
        n = rnd.next(4, 160);
        int dominant = rnd.next(0, 3);
        int rare = rnd.next(0, 3);
        while (rare == dominant) rare = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            dna += rnd.next(0, 9) < 8 ? bases[dominant] : bases[rare];
        }
    } else if (mode == 5) {
        n = rnd.next(2, 150);
        string pattern;
        int period = rnd.next(2, 4);
        for (int i = 0; i < period; ++i) pattern += rnd.any(bases);
        for (int i = 0; i < n; ++i) dna += pattern[i % period];
    } else if (mode == 6) {
        n = rnd.next(10, 250);
        int blockCount = rnd.next(2, 8);
        for (int block = 0; block < blockCount; ++block) {
            int remaining = n - (int)dna.size();
            int len = block == blockCount - 1 ? remaining : rnd.next(1, max(1, remaining / 2));
            dna.append(len, rnd.any(bases));
        }
        if ((int)dna.size() < n) dna.append(n - dna.size(), rnd.any(bases));
    } else if (mode == 7) {
        n = rnd.next(200, 1000);
        dna = randomDna(n, bases);
    } else {
        n = rnd.next(1000, 10000);
        dna = randomDna(n, bases);
    }

    println(n);
    println(dna);
    return 0;
}
