#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: length of the string
    int N = rnd.next(1, 15);
    // Maximum underscores is at most 10 and at most N
    int uMax = min(N, 10);
    // Skew factor for number of underscores
    int t = rnd.next(-3, 3);
    // Number of underscores, weighted sampling for diversity
    int u = rnd.wnext(uMax + 1, t);  // in [0, uMax]

    // Hyper-parameter: probability of vowel vs consonant
    double vowelProb = rnd.next();
    string vowels = "AEIOU";
    string consonants;
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (vowels.find(c) == string::npos) consonants.push_back(c);
    }

    // Build initial string with random letters
    string s;
    s.reserve(N);
    for (int i = 0; i < N; ++i) {
        if (rnd.next() < vowelProb)
            s.push_back(rnd.any(vowels));
        else
            s.push_back(rnd.any(consonants));
    }

    // Choose positions for underscores
    vector<int> pos(N);
    iota(pos.begin(), pos.end(), 0);
    shuffle(pos.begin(), pos.end());
    for (int i = 0; i < u; ++i) {
        s[pos[i]] = '_';
    }

    // Output the single test case
    println(s);
    return 0;
}
