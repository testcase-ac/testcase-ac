#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string S = inf.readLine("[a-z]{1,1000000}", "S");

    string T = inf.readLine("[a-z]{1,1000000}", "T");
    ensuref((int)T.size() <= (int)S.size(),
            "Length of T (%d) must be at most length of S (%d)",
            (int)T.size(), (int)S.size());

    vector<int> pi(T.size(), 0);
    for (int i = 1; i < (int)T.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && T[i] != T[j]) {
            j = pi[j - 1];
        }
        if (T[i] == T[j]) {
            ++j;
        }
        pi[i] = j;
    }

    string res;
    res.reserve(S.size());
    vector<int> matched;
    matched.reserve(S.size());

    for (char c : S) {
        int k = matched.empty() ? 0 : matched.back();
        while (k > 0 && c != T[k]) {
            k = pi[k - 1];
        }
        if (c == T[k]) {
            ++k;
        }

        res.push_back(c);
        matched.push_back(k);

        if (k == (int)T.size()) {
            for (int i = 0; i < (int)T.size(); ++i) {
                res.pop_back();
                matched.pop_back();
            }
        }
    }

    ensuref(!res.empty(),
            "Final censored string S became empty, which is forbidden by the statement.");

    inf.readEof();
}
