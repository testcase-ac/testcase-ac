#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n;
vector<pair<int,int>> cables;               // input cables as (A, B)
unordered_map<int,int> a2b;                // map from A-position to B-position

// Reads an answer (either jury's or participant's), verifies its correctness,
// and returns the list of removed A-positions.
vector<int> readAns(InStream &stream) {
    // Read k = number of removed cables
    int k = stream.readInt(0, n, "number of removed cables");
    vector<int> rem(k);
    for (int i = 0; i < k; i++) {
        rem[i] = stream.readInt(1, 500000, format("a[%d]", i+1).c_str());
    }
    // Check that the list is strictly increasing
    for (int i = 1; i < k; i++) {
        if (rem[i] <= rem[i-1]) {
            stream.quitf(_wa,
                         "removed A-positions not strictly increasing at index %d: %d after %d",
                         i+1, rem[i], rem[i-1]);
        }
    }
    // Check existence and duplicates
    unordered_set<int> rem_set;
    rem_set.reserve(k*2+1);
    for (int a : rem) {
        if (!a2b.count(a)) {
            stream.quitf(_wa, "no cable at A-position %d", a);
        }
        if (!rem_set.insert(a).second) {
            stream.quitf(_wa, "duplicate removal of cable at A-position %d", a);
        }
    }
    // Build the list of remaining cables and check for crossings
    vector<pair<int,int>> remain;
    remain.reserve(n - k);
    for (auto &pr : cables) {
        int a = pr.first, b = pr.second;
        if (!rem_set.count(a))
            remain.emplace_back(a, b);
    }
    sort(remain.begin(), remain.end(),
         [](auto &L, auto &R) { return L.first < R.first; });
    int prevB = 0;  // since all B >= 1
    for (auto &pr : remain) {
        int a = pr.first, b = pr.second;
        if (b <= prevB) {
            stream.quitf(_wa,
                         "cables cross: cable at A=%d with B=%d after B<=%d",
                         a, b, prevB);
        }
        prevB = b;
    }
    return rem;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    n = inf.readInt();
    cables.resize(n);
    a2b.reserve(n*2+1);
    for (int i = 0; i < n; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        cables[i] = {a, b};
        a2b[a] = b;
    }
    // Read and verify jury's and participant's answers
    vector<int> jury_rem = readAns(ans);
    vector<int> part_rem = readAns(ouf);
    int j = (int)jury_rem.size();
    int p = (int)part_rem.size();
    // Compare
    if (p > j) {
        quitf(_wa, "too many cables removed: minimal is %d, found %d", j, p);
    } else if (p < j) {
        quitf(_fail,
              "participant removed fewer cables (%d) than minimal (%d)", p, j);
    } else {
        quitf(_ok, "removed %d cables", p);
    }
    return 0;
}
