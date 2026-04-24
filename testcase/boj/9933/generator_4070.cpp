#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: number of words (small for hand-checkable)
    int biasN = rnd.next(-1, 1); // -1 small, 0 uniform, 1 large
    int n0;
    if (biasN == 0) {
        n0 = rnd.next(8);       // 0..8
    } else {
        n0 = rnd.wnext(8, biasN); // weighted
    }
    int N = n0 + 2; // final N in [2..10]

    // Hyper-parameter for alphabet size K (letters 'a'..'a'+K-1)
    int biasA = rnd.next(-1, 1);
    int a0;
    if (biasA == 0) {
        a0 = rnd.next(3, 26);
    } else {
        a0 = rnd.wnext(24, biasA) + 3; // makes [3..26]
    }
    int K = a0;

    // Hyper-parameter for password length L: odd between 3 and 13
    int biasL = rnd.next(-1, 1);
    int idx;
    if (biasL == 0) {
        idx = rnd.next(6);      // 0..5
    } else {
        idx = rnd.wnext(6, biasL);
    }
    int L = 2*(idx + 1) + 1; // 3,5,...,13

    // Generate a non-palindromic password pw and its reverse rpw
    string pw, rpw;
    do {
        pw.clear();
        for (int i = 0; i < L; i++) {
            pw.push_back(char('a' + rnd.next(K-1)));
        }
        rpw = pw;
        reverse(rpw.begin(), rpw.end());
    } while (pw == rpw);

    set<string> S;
    vector<string> words;
    // ensure only one valid pair pw <-> rpw
    S.insert(pw);
    S.insert(rpw);
    words.push_back(pw);
    words.push_back(rpw);

    // Fill the rest with odd-length non-palindromic words avoiding any reverse conflicts
    while ((int)words.size() < N) {
        int l = 2 * rnd.next(1, 6) + 1; // random odd length 3..13
        string w;
        w.reserve(l);
        for (int i = 0; i < l; i++) {
            w.push_back(char('a' + rnd.next(K-1)));
        }
        string rw = w;
        reverse(rw.begin(), rw.end());
        // skip palindromes and any word whose reverse or itself is already used
        if (w == rw) continue;
        if (S.count(w) || S.count(rw)) continue;
        S.insert(w);
        words.push_back(w);
    }

    // Shuffle and output
    shuffle(words.begin(), words.end());
    println(N);
    for (auto &w : words)
        println(w);

    return 0;
}
