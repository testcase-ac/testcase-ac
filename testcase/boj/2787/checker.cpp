#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Constraint {
    int type, x, y, v;
};

vector<int> readSeq(InStream &stream) {
    vector<int> res;
    // Read all integers until EOF
    while (!stream.seekEof()) {
        int x = stream.readInt(-1000000000, 1000000000, "output");
        res.push_back(x);
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    int N = inf.readInt();
    int M = inf.readInt();
    vector<Constraint> cons(M);
    for (int i = 0; i < M; i++) {
        cons[i].type = inf.readInt(1, 2);
        cons[i].x    = inf.readInt(1, N);
        cons[i].y    = inf.readInt(cons[i].x, N);
        cons[i].v    = inf.readInt(1, N);
    }
    // Read jury and participant outputs
    vector<int> jAns = readSeq(ans);
    vector<int> pAns = readSeq(ouf);

    // Case: no solution (-1)
    if ((int)jAns.size() == 1 && jAns[0] == -1) {
        // Jury says impossible
        if ((int)pAns.size() == 1 && pAns[0] == -1) {
            quitf(_ok, "both say -1");
        } else {
            quitf(_wa, "expected -1 (no solution), found a sequence");
        }
    }

    // Jury provides a solution
    // Validate jury's output format minimally
    if ((int)jAns.size() != N) {
        ans.quitf(_fail, "jury's output length = %d, expected %d", (int)jAns.size(), N);
    }
    // Now check participant didn't say -1
    if ((int)pAns.size() == 1 && pAns[0] == -1) {
        quitf(_wa, "participant says -1 but a solution exists");
    }
    // Check length
    if ((int)pAns.size() != N) {
        quitf(_wa, "expected %d numbers, found %d", N, (int)pAns.size());
    }
    // Check values in [1..N] and distinctness
    vector<bool> seen(N+1, false);
    for (int i = 0; i < N; i++) {
        int x = pAns[i];
        if (x < 1 || x > N) {
            quitf(_wa, "value %d at position %d is out of range [1..%d]", x, i+1, N);
        }
        if (seen[x]) {
            quitf(_wa, "value %d appears more than once", x);
        }
        seen[x] = true;
    }
    // Check all constraints
    for (int i = 0; i < M; i++) {
        int l = cons[i].x - 1;
        int r = cons[i].y - 1;
        int v = cons[i].v;
        if (cons[i].type == 1) {
            // max
            int got = pAns[l];
            for (int j = l+1; j <= r; j++) got = max(got, pAns[j]);
            if (got != v) {
                quitf(_wa,
                      "constraint %d: max over [%d,%d] should be %d, found %d",
                      i+1, cons[i].x, cons[i].y, v, got);
            }
        } else {
            // min
            int got = pAns[l];
            for (int j = l+1; j <= r; j++) got = min(got, pAns[j]);
            if (got != v) {
                quitf(_wa,
                      "constraint %d: min over [%d,%d] should be %d, found %d",
                      i+1, cons[i].x, cons[i].y, v, got);
            }
        }
    }
    // All good
    quitf(_ok, "valid permutation");
    return 0;
}
