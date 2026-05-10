#include "testlib.h"
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // 2. Read S_1..S_N
    int qmark_count = 0, qmark_pos = -1;
    vector<string> S(N);
    set<string> used_words;
    for (int i = 0; i < N; ++i) {
        string s = inf.readToken("[a-z\\?]{1,10}", "S_i");
        inf.readEoln();
        if (s == "?") {
            ++qmark_count;
            ensuref(qmark_count == 1, "There must be exactly one '?', found more at position %d", i+1);
            qmark_pos = i;
            S[i] = s;
        } else {
            int len = s.length();
            ensuref(2 <= len && len <= 10, "S_%d: length must be between 2 and 10, got %d", i+1, len);
            ensuref(all_of(s.begin(), s.end(), [](char c){ return 'a' <= c && c <= 'z'; }),
                    "S_%d: must be all lowercase letters", i+1);
            ensuref(!used_words.count(s), "S_%d: duplicate word '%s' in record", i+1, s.c_str());
            used_words.insert(s);
            S[i] = s;
        }
    }
    ensuref(qmark_count == 1, "There must be exactly one '?', found %d", qmark_count);

    // 3. Read M
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // 4. Read A_1..A_M
    vector<string> A(M);
    set<string> candidate_set;
    for (int i = 0; i < M; ++i) {
        string a = inf.readToken("[a-z]{2,10}", "A_i");
        inf.readEoln();
        ensuref(candidate_set.count(a) == 0, "A_%d: duplicate candidate word '%s'", i+1, a.c_str());
        candidate_set.insert(a);
        A[i] = a;
    }

    // 5. Check that exactly one candidate can be placed at '?'
    int idx = qmark_pos;

    // Prepare set of used words (excluding '?')
    set<string> used = used_words;

    vector<string> possible;
    for (const string& cand : A) {
        // Not used in S
        if (used.count(cand)) continue;

        // Check prev-last
        if (idx > 0 && S[idx-1] != "?") {
            char prev_last = S[idx-1].back();
            if (cand[0] != prev_last) continue;
        }
        // Check next-first
        if (idx < N-1 && S[idx+1] != "?") {
            char next_first = S[idx+1][0];
            if (cand.back() != next_first) continue;
        }

        // Check that the resulting sequence is a valid chain (no duplicate, each word's last char matches next's first char)
        // Build the sequence with cand inserted at idx
        vector<string> T = S;
        T[idx] = cand;
        set<string> seen;
        bool valid = true;
        for (int i = 0; i < N; ++i) {
            if (seen.count(T[i])) {
                valid = false;
                break;
            }
            seen.insert(T[i]);
            if (i > 0) {
                if (T[i-1].back() != T[i][0]) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid) possible.push_back(cand);
    }
    ensuref(possible.size() == 1,
        "There must be exactly one candidate that fits, found %zu", possible.size());

    inf.readEof();
}
