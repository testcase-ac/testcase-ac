#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char * argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    int N = inf.readInt();
    int T = inf.readInt();
    vector<long long> seq(N);
    for (int i = 0; i < N; i++) {
        seq[i] = inf.readInt();
    }

    // Read contestant's operations
    vector<int> ops;
    for (int k = 0; k < N - 1; k++) {
        if (ouf.seekEof()) {
            quitf(_wa, "too few operations: expected %d, found %d", N - 1, k);
        }
        int x = ouf.readInt();
        ops.push_back(x);
    }
    // Check for extra tokens
    if (!ouf.seekEof()) {
        string extra = ouf.readToken();
        quitf(_wa, "extra token in output: '%s'", extra.c_str());
    }

    // Simulate the reduction operations
    vector<long long> v = seq;
    for (int step = 0; step < (int)ops.size(); step++) {
        int idx = ops[step];
        int len = (int)v.size();
        if (idx < 1 || idx > len - 1) {
            quitf(_wa, "operation %d: index %d out of range [1, %d]", step + 1, idx, len - 1);
        }
        // perform CON(v, idx): v[idx-1] = v[idx-1] - v[idx], then remove v[idx]
        v[idx - 1] = v[idx - 1] - v[idx];
        v.erase(v.begin() + idx);
    }

    // After N-1 ops, must have exactly one number
    if ((int)v.size() != 1) {
        quitf(_fail, "internal error: sequence length is %d after %d operations, expected 1",
              (int)v.size(), N - 1);
    }

    // Check final value
    if (v[0] != T) {
        quitf(_wa, "final value is %lld, expected %d", v[0], T);
    }

    quitf(_ok, "correct");
}
