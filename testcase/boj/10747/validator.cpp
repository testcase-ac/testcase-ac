#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read S: non-empty, lowercase letters, length <= 1e6
    string S = inf.readLine("[a-z]{1,1000000}", "S");

    // Read T: non-empty, lowercase letters, length <= |S|
    string T = inf.readLine("[a-z]{1,1000000}", "T");
    ensuref((int)T.size() <= (int)S.size(),
            "Length of T (%d) must be at most length of S (%d)",
            (int)T.size(), (int)S.size());

    // Simulate the censoring process to ensure that S will not become empty
    // Use a stack-like string plus matched-length stack for efficient checking.
    int nT = (int)T.size();
    string res;
    res.reserve(S.size());
    vector<int> matched; // length of current matched suffix vs T prefix
    matched.reserve(S.size());

    for (char c : S) {
        res.push_back(c);
        int k = matched.empty() ? 0 : matched.back();
        while (k > 0 && T[k] != c) k = 0; // since characters are simple, we can just reset
        if (T[k] == c) k++;
        else if (T[0] == c) k = 1;
        else k = 0;

        matched.push_back(k);

        if (k == nT) {
            // remove last nT characters
            for (int i = 0; i < nT; ++i) {
                res.pop_back();
                matched.pop_back();
            }
        }
    }

    ensuref(!res.empty(), "Final censored string S became empty, which is forbidden by the statement.");

    inf.readEof();
}
