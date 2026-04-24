#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of strings in S
    int N = rnd.next(1, 10);
    // Choose alphabet size from some options for diversity
    vector<int> sigmaOptions = {2, 3, 5, 10, 26};
    int sigma = rnd.any(sigmaOptions);
    // Compute minimal length so that sigma^minLen >= N (to avoid infinite loops)
    int minimalLen = 1;
    if (sigma > 1) {
        minimalLen = max(1, (int)ceil(log((double)N) / log((double)sigma)));
    }
    // Max length of strings in S
    int maxLen = rnd.next(minimalLen, min(minimalLen + 5, 10));
    // Probability to pick a prefix as query
    double prefixProb = rnd.next();

    // Generate unique set S of N strings
    set<string> Sset;
    while ((int)Sset.size() < N) {
        int len = rnd.next(1, maxLen);
        string s;
        s.reserve(len);
        for (int i = 0; i < len; i++) {
            s.push_back(char('a' + rnd.next(0, sigma - 1)));
        }
        Sset.insert(s);
    }
    vector<string> S(Sset.begin(), Sset.end());
    shuffle(S.begin(), S.end());

    // Build list of all distinct prefixes from S
    set<string> prefSet;
    vector<string> prefList;
    for (auto &s : S) {
        for (int l = 1; l <= (int)s.size(); l++) {
            string p = s.substr(0, l);
            if (prefSet.insert(p).second) {
                prefList.push_back(p);
            }
        }
    }

    // Number of queries
    int M = rnd.next(1, 20);
    vector<string> Q;
    Q.reserve(M);
    for (int i = 0; i < M; i++) {
        if (!prefList.empty() && rnd.next() < prefixProb) {
            // pick a valid prefix
            Q.push_back(rnd.any(prefList));
        } else {
            // generate a string that is NOT a prefix of any in S
            string q;
            do {
                int len = rnd.next(1, maxLen + 2);
                q.clear();
                q.reserve(len);
                for (int j = 0; j < len; j++) {
                    q.push_back(char('a' + rnd.next(0, sigma - 1)));
                }
            } while (prefSet.count(q));
            Q.push_back(q);
        }
    }

    // Output
    println(N, M);
    for (auto &s : S) println(s);
    for (auto &q : Q) println(q);

    return 0;
}
