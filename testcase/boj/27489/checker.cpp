#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Output {
    bool yes;
    vector<pair<int,int>> pairs;
};

// Reads from stream the answer for one test case with given n.
// Does not check correctness of the pairing itself, only parses it.
// On parse error in contestant output, quit with _wa; in jury output, quit with _fail.
Output readAnswer(InStream &stream, int n, int testNum) {
    Output out;
    string tok = stream.readToken();
    // normalize
    for (auto &c : tok) c = tolower(c);
    if (tok != "yes" && tok != "no") {
        if (&stream == &ouf)
            stream.quitf(_wa, "test case #%d: expected 'Yes' or 'No', found '%s'", testNum, tok.c_str());
        else
            stream.quitf(_fail, "test case #%d (jury): expected 'Yes' or 'No', found '%s'", testNum, tok.c_str());
    }
    out.yes = (tok == "yes");
    if (out.yes) {
        out.pairs.reserve(n);
        for (int i = 0; i < n; i++) {
            int a = stream.readInt(1, 2*n, format("test case #%d: a[%d]", testNum, i+1).c_str());
            int b = stream.readInt(1, 2*n, format("test case #%d: b[%d]", testNum, i+1).c_str());
            out.pairs.emplace_back(a, b);
        }
    }
    return out;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt();
    for (int tc = 1; tc <= t; tc++) {
        int n = inf.readInt();
        // Read jury and participant outputs for this test case
        Output jury = readAnswer(ans, n, tc);
        Output part = readAnswer(ouf, n, tc);
        // Compare yes/no
        if (!jury.yes && !part.yes) {
            // both no: ok, continue
            continue;
        }
        if (jury.yes && !part.yes) {
            quitf(_wa, "test case #%d: jury has a solution but participant says 'No'", tc);
        }
        if (!jury.yes && part.yes) {
            quitf(_wa, "test case #%d: participant says 'Yes' but jury says 'No'", tc);
        }
        // both say yes -> validate participant's pairing
        vector<char> used(2*n+1, 0);
        vector<int> sums;
        sums.reserve(n);
        for (int i = 0; i < n; i++) {
            int a = part.pairs[i].first;
            int b = part.pairs[i].second;
            // check distinctness in pair
            if (a == b) {
                quitf(_wa, "test case #%d: pair %d has identical elements %d and %d", tc, i+1, a, b);
            }
            // check each number used exactly once
            if (used[a]) {
                quitf(_wa, "test case #%d: number %d is used more than once", tc, a);
            }
            used[a] = 1;
            if (used[b]) {
                quitf(_wa, "test case #%d: number %d is used more than once", tc, b);
            }
            used[b] = 1;
            sums.push_back(a + b);
        }
        // check all numbers used
        for (int x = 1; x <= 2*n; x++) {
            if (!used[x]) {
                quitf(_wa, "test case #%d: number %d is missing in the pairing", tc, x);
            }
        }
        // check sums are consecutive
        sort(sums.begin(), sums.end());
        for (int i = 1; i < n; i++) {
            if (sums[i] != sums[i-1] + 1) {
                quitf(_wa, "test case #%d: sums are not consecutive at index %d: %d and %d",
                      tc, i, sums[i-1], sums[i]);
            }
        }
    }
    // Ensure no extra output
    ouf.readEof();
    quitf(_ok, "OK");
    return 0;
}
