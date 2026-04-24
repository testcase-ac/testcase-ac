#include "testlib.h"
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of words
    int N = inf.readInt(2, 100, "N");
    inf.readEoln();

    vector<string> words;
    words.reserve(N);

    // Read each word
    for (int i = 0; i < N; i++) {
        // word: lowercase only, length between 3 and 13
        string s = inf.readToken("[a-z]{3,13}", "word");
        // must be odd length
        ensuref((int)s.size() % 2 == 1,
                "Word %d has even length %d", i + 1, (int)s.size());
        inf.readEoln();
        words.push_back(s);
    }

    // Build set of distinct words
    set<string> st(words.begin(), words.end());

    // Collect all words whose reverse is also present
    vector<string> candidates;
    for (auto &w : st) {
        string rev = w;
        reverse(rev.begin(), rev.end());
        if (st.count(rev)) {
            candidates.push_back(w);
        }
    }

    // There must be at least one candidate
    ensuref(!candidates.empty(),
            "No password candidate found (no word whose reverse is present)");

    // Compute the expected answer from the first candidate
    int ans_len = (int)candidates[0].size();
    char ans_mid = candidates[0][ans_len / 2];

    // Ensure all candidates produce the same (length, middle char)
    for (size_t i = 1; i < candidates.size(); i++) {
        const string &w = candidates[i];
        int L = (int)w.size();
        char M = w[L / 2];
        ensuref(L == ans_len,
                "Candidates '%s' and '%s' produce different lengths: %d vs %d",
                candidates[0].c_str(), w.c_str(), ans_len, L);
        ensuref(M == ans_mid,
                "Candidates '%s' and '%s' produce different middle chars: '%c' vs '%c'",
                candidates[0].c_str(), w.c_str(), ans_mid, M);
    }

    inf.readEof();
    return 0;
}
