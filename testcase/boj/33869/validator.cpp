#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read W: 1 <= |W| <= 20, uppercase letters only, no spaces
    string W = inf.readToken("[A-Z]{1,20}", "W");
    inf.readEoln();

    // Read S: 1 <= |S| <= 200, uppercase letters only, no spaces
    string S = inf.readToken("[A-Z]{1,200}", "S");
    inf.readEoln();

    // Build word key from W: first occurrence of each letter in order
    vector<bool> used(26, false);
    string key;
    key.reserve(26);
    for (char c : W) {
        int idx = c - 'A';
        if (!used[idx]) {
            used[idx] = true;
            key.push_back(c);
        }
    }

    // Complete the substitution alphabet: key + remaining letters in order
    string sub;
    sub.reserve(26);
    sub += key;
    for (int i = 0; i < 26; ++i) {
        if (!used[i]) sub.push_back(char('A' + i));
    }

    ensuref((int)sub.size() == 26, "Substitution alphabet must have length 26, got %d", (int)sub.size());

    // Build mapping from plaintext A..Z to cipher letters
    char mapP2C[26];
    for (int i = 0; i < 26; ++i) {
        mapP2C[i] = sub[i];
    }

    // Encrypt S and (optionally) ensure no unexpected behavior
    string enc;
    enc.reserve(S.size());
    for (char c : S) {
        int idx = c - 'A';
        ensuref(0 <= idx && idx < 26, "Character in S out of A-Z range");
        enc.push_back(mapP2C[idx]);
    }

    // No extra lines allowed
    inf.readEof();
}
