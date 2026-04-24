#include "testlib.h"
#include <vector>
#include <string>
#include <utility>
using namespace std;

int k, n;
vector<vector<pair<int,char>>> pred;

// readAns reads an answer from stream (ans or ouf), checks its validity,
// and returns the assignment as a vector<char> of size k.
// If the answer is "-1", returns an empty vector.
// On invalid output: if stream==ouf, quits with _wa; if stream==ans, quits with _fail.
vector<char> readAns(InStream &stream) {
    string s = stream.readToken();
    if (s == "-1") {
        // no assignment
        return vector<char>();
    }
    // must be a string of length k, with only R or B
    if ((int)s.size() != k)
        stream.quitf(_wa, "output length is %d, expected %d", (int)s.size(), k);
    vector<char> res(k);
    for (int i = 0; i < k; i++) {
        if (s[i] != 'R' && s[i] != 'B')
            stream.quitf(_wa, "invalid color '%c' at position %d", s[i], i + 1);
        res[i] = s[i];
    }
    // check that each participant has at least 2 matches
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (auto &pr : pred[i]) {
            int lamp = pr.first;
            char want = pr.second;
            if (res[lamp - 1] == want)
                cnt++;
        }
        if (cnt < 2) {
            stream.quitf(_wa,
                "assignment '%s' fails for participant %d (only %d matches)",
                s.c_str(), i + 1, cnt);
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // read input
    k = inf.readInt();       // number of lamps
    n = inf.readInt();       // number of participants
    pred.assign(n, vector<pair<int,char>>());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            int lamp = inf.readInt(1, k);
            string cs = inf.readToken();
            char c = cs[0]; // 'R' or 'B'
            pred[i].push_back({lamp, c});
        }
    }
    // read jury and participant answers
    vector<char> jans = readAns(ans);
    vector<char> pans = readAns(ouf);

    bool jury_impossible = jans.empty();
    bool part_impossible = pans.empty();

    if (jury_impossible && part_impossible) {
        // both say impossible
        quitf(_ok, "both outputs are -1");
    }
    if (jury_impossible && !part_impossible) {
        // jury says no solution, participant found one
        quitf(_wa, "no solution exists but participant provides an assignment");
    }
    if (!jury_impossible && part_impossible) {
        // jury has a solution, participant says -1
        quitf(_wa, "solution exists but participant outputs -1");
    }
    // both provided valid assignments; since any valid assignment is OK, accept
    quitf(_ok, "valid assignment");
}
