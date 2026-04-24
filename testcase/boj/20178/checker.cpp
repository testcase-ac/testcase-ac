#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int N;
vector<vector<int>> A;

// Reads an answer (jury or participant) from 'stream'.
// Returns an empty vector if the answer is "-1" (impossible).
// Otherwise returns a vector of N rows, each row is the list of switches to turn on.
// On any format or correctness error: quits with _wa if stream==ouf, or _fail if stream==ans.
vector<vector<int>> readAns(InStream &stream) {
    // Try to read the first integer (could be -1 or first switch of row 1)
    stream.skipBlanks();
    if (stream.eof())
        stream.quitf(_wa, "unexpected end of answer");
    int first = stream.readInt();  // no bounds yet
    if (first == -1) {
        // must be the only token (modulo whitespace)
        stream.skipBlanks();
        if (!stream.eof())
            stream.quitf(_wa, "extra token after -1");
        return vector<vector<int>>(); // empty signals impossible
    }
    // Otherwise, first is the first switch index of row 0
    vector<vector<int>> rows(N);
    // process row 0
    if (first < 1 || first > N)
        stream.quitf(_wa, "switch index %d out of range [1..%d]", first, N);
    rows[0].push_back(first);
    // read the rest of row 0 until end-of-line
    while (!stream.eoln()) {
        int x = stream.readInt(1, N, "switch index");
        rows[0].push_back(x);
    }
    stream.readEoln();
    // read rows 1..N-1
    for (int i = 1; i < N; i++) {
        // read zero or more switches until end-of-line
        while (!stream.eoln()) {
            int x = stream.readInt(1, N, "switch index");
            rows[i].push_back(x);
        }
        stream.readEoln();
    }
    // no extra tokens
    stream.skipBlanks();
    if (!stream.eof())
        stream.quitf(_wa, "extra data after reading %d lines", N);
    // check each row: sorted strictly increasing
    for (int i = 0; i < N; i++) {
        auto &r = rows[i];
        if (!is_sorted(r.begin(), r.end()))
            stream.quitf(_wa, "switch list for light %d is not sorted", i+1);
        for (int j = 1; j < (int)r.size(); j++) {
            if (r[j] == r[j-1])
                stream.quitf(_wa, "duplicate switch %d in list for light %d", r[j], i+1);
        }
    }
    // validate toggling
    for (int target = 0; target < N; target++) {
        vector<int> state(N, 0);
        // apply each switch in rows[target]
        for (int sw : rows[target]) {
            int si = sw - 1;
            for (int light = 0; light < N; light++) {
                if (A[si][light]) state[light] ^= 1;
            }
        }
        // check final state: only state[target]==1
        for (int light = 0; light < N; light++) {
            if (light == target) {
                if (state[light] != 1)
                    stream.quitf(_wa, "light %d is off but should be on", target+1);
            } else {
                if (state[light] != 0)
                    stream.quitf(_wa, "light %d is on but should be off for target %d",
                                  light+1, target+1);
            }
        }
    }
    return rows;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // read input
    N = inf.readInt(3, 500);
    A.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = inf.readInt(0, 1);
        }
    }
    // read jury and participant answers
    auto jans = readAns(ans);
    auto pans = readAns(ouf);
    bool j_imp = jans.empty();
    bool p_imp = pans.empty();
    if (j_imp && p_imp) {
        quitf(_ok, "both say impossible");
    }
    if (j_imp && !p_imp) {
        quitf(_wa, "participant provides a solution but jury says impossible");
    }
    if (!j_imp && p_imp) {
        quitf(_wa, "participant says impossible but solution exists");
    }
    // both have valid solutions -> accept any
    quitf(_ok, "valid solution");
    return 0;
}
