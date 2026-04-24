#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static vector<string> split_by_space(const string &s) {
    vector<string> res;
    int n = s.size();
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && s[j] != ' ') j++;
        res.push_back(s.substr(i, j - i));
        i = j + 1;
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read the N sentences S_i
    unordered_set<string> seen;
    for (int i = 1; i <= N; i++) {
        string line = inf.readLine("[^]+", "S_line");
        // Check no leading/trailing/multiple spaces
        ensuref(!line.empty(), "S_%d is empty", i);
        ensuref(line.front() != ' ', "S_%d has leading space", i);
        ensuref(line.back() != ' ',  "S_%d has trailing space", i);
        ensuref(line.find("  ") == string::npos, "S_%d has consecutive spaces", i);

        // Split into words
        vector<string> toks = split_by_space(line);
        ensuref((int)toks.size() >= 1 && (int)toks.size() <= 100,
                "S_%d has invalid word count %d (must be 1..100)", i, (int)toks.size());

        // Check each word
        for (const string &w : toks) {
            ensuref((int)w.size() >= 1 && (int)w.size() <= 32,
                    "S_%d contains word of invalid length %d: '%s'",
                    i, (int)w.size(), w.c_str());
            for (char c : w) {
                ensuref(c >= 'a' && c <= 'z',
                        "S_%d contains invalid character in word '%s'", i, w.c_str());
            }
            // Check global uniqueness across all S_i
            ensuref(!seen.count(w),
                    "Duplicate word across parrots in S_%d: '%s'", i, w.c_str());
            seen.insert(w);
        }
    }

    // Read the recorded sentence L
    string L_line = inf.readLine("[^]+", "L_line");
    ensuref(!L_line.empty(), "L is empty");
    ensuref(L_line.front() != ' ', "L has leading space");
    ensuref(L_line.back() != ' ',  "L has trailing space");
    ensuref(L_line.find("  ") == string::npos, "L has consecutive spaces");

    vector<string> L_toks = split_by_space(L_line);
    ensuref((int)L_toks.size() >= 1 && (int)L_toks.size() <= 10000,
            "L has invalid word count %d (must be 1..10000)", (int)L_toks.size());

    for (const string &w : L_toks) {
        ensuref((int)w.size() >= 1 && (int)w.size() <= 32,
                "L contains word of invalid length %d: '%s'",
                (int)w.size(), w.c_str());
        for (char c : w) {
            ensuref(c >= 'a' && c <= 'z',
                    "L contains invalid character in word '%s'", w.c_str());
        }
    }

    inf.readEof();
    return 0;
}
