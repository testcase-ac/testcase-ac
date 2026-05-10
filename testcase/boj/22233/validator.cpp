#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 200000;
    const int MAX_M = 200000;
    const int MAX_LEN = 10;

    int N = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int M = inf.readInt(1, MAX_M, "M");
    inf.readEoln();

    // Read N unique initial keywords
    unordered_set<string> memo;
    memo.reserve(N * 2);
    memo.max_load_factor(0.7);

    auto isValidKeywordChar = [](char c) {
        return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
    };

    for (int i = 0; i < N; ++i) {
        string s = inf.readToken("[a-z0-9]{1,10}", "keyword");
        inf.readEoln();

        ensuref((int)s.size() >= 1 && (int)s.size() <= MAX_LEN,
                "Keyword length out of bounds at line %d: '%s' (len=%d)",
                i + 2, s.c_str(), (int)s.size());

        auto it = memo.find(s);
        ensuref(it == memo.end(),
                "Duplicate memo keyword at line %d: '%s'",
                i + 2, s.c_str());

        memo.insert(s);
    }

    // We will also check that keywords in each article line are distinct.
    // Additionally, we simulate the process to ensure that keywords
    // referenced by articles are subsets of memo at some point (if
    // problem implicitly requires that), but here statement allows that
    // a keyword may not be in memo (it just won't be erased), so we do
    // NOT enforce membership.

    // Process M article lines
    for (int i = 0; i < M; ++i) {
        string line = inf.readLine("[^]+", "article_keywords");
        // Line must be non-empty
        ensuref(!line.empty(),
                "Empty keyword list in article line %d",
                N + 2 + i);

        // Split by commas, no spaces allowed
        vector<string> kws;
        string cur;
        for (char c : line) {
            if (c == ',') {
                // separator: previous token must be non-empty
                ensuref(!cur.empty(),
                        "Empty keyword between commas in article line %d",
                        N + 2 + i);
                kws.push_back(cur);
                cur.clear();
            } else {
                ensuref(c != ' ' && c != '\t' && c != '\r',
                        "Whitespace is not allowed inside article keyword list at line %d",
                        N + 2 + i);
                ensuref(isValidKeywordChar(c),
                        "Invalid character '%c' in keyword at article line %d",
                        c, N + 2 + i);
                cur.push_back(c);
                ensuref((int)cur.size() <= MAX_LEN,
                        "Keyword length exceeds %d in article line %d",
                        MAX_LEN, N + 2 + i);
            }
        }
        // last token
        ensuref(!cur.empty(),
                "Empty last keyword (line ends with comma) in article line %d",
                N + 2 + i);
        kws.push_back(cur);

        int K = (int)kws.size();
        ensuref(1 <= K && K <= 10,
                "Number of keywords in article line %d is %d, must be in [1,10]",
                N + 2 + i, K);

        // Check that keywords in this article are distinct
        {
            unordered_set<string> seen;
            seen.reserve(K * 2);
            seen.max_load_factor(0.7);
            for (int j = 0; j < K; ++j) {
                const string &w = kws[j];
                auto it2 = seen.find(w);
                ensuref(it2 == seen.end(),
                        "Duplicate keyword '%s' inside the same article at line %d",
                        w.c_str(), N + 2 + i);
                seen.insert(w);
            }
        }

        // Simulate erase-from-memo behavior
        for (const string &w : kws) {
            auto it = memo.find(w);
            if (it != memo.end()) memo.erase(it);
        }

        // After each article, the intended solution prints the memo size.
        // No explicit upper bound constraint other than initial N, so
        // no extra validation needed here.
    }

    inf.readEof();
}
