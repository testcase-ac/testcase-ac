#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and N
    int K = inf.readInt(1, 100000, "K");
    inf.readSpace();
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read K distinct words, track which initial letters appear
    set<string> seen;
    bool has_initial[26] = {false};
    for (int i = 0; i < K; i++) {
        // word: lowercase only, length 1..21
        string w = inf.readToken("[a-z]{1,21}", "word");
        inf.readEoln();
        // Check distinctness
        bool inserted = seen.insert(w).second;
        ensuref(inserted, "Duplicate word at index %d: %s", i, w.c_str());
        // Mark initial letter
        int idx = w[0] - 'a';
        has_initial[idx] = true;
    }

    // Read N letters, ensure each has at least one word starting with it
    for (int i = 0; i < N; i++) {
        string t = inf.readToken("[a-z]", "letter");
        inf.readEoln();
        char c = t[0];
        int idx = c - 'a';
        ensuref(has_initial[idx],
                "No word starts with letter '%c' at position %d", c, i);
    }

    inf.readEof();
    return 0;
}
