#include "testlib.h"
#include <vector>
using namespace std;

int N, T;
vector<long long> seq;

void readAns(InStream& stream) {
    vector<int> ops;
    for (int k = 0; k < N - 1; k++) {
        if (stream.seekEof()) {
            stream.quitf(_wa, "too few operations: expected %d, found %d", N - 1, k);
        }
        int x = stream.readInt();
        ops.push_back(x);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d operation(s)", N - 1);
    }

    vector<long long> v = seq;
    for (int step = 0; step < (int)ops.size(); step++) {
        int idx = ops[step];
        int len = (int)v.size();
        if (idx < 1 || idx > len - 1) {
            stream.quitf(_wa, "operation %d: index %d out of range [1, %d]", step + 1, idx, len - 1);
        }
        v[idx - 1] = v[idx - 1] - v[idx];
        v.erase(v.begin() + idx);
    }

    if ((int)v.size() != 1) {
        quitf(_fail, "internal error: sequence length is %d after %d operations, expected 1",
              (int)v.size(), N - 1);
    }
    if (v[0] != T) {
        stream.quitf(_wa, "final value is %lld, expected %d", v[0], T);
    }
}

int main(int argc, char * argv[]) {
    registerTestlibCmd(argc, argv);

    N = inf.readInt();
    T = inf.readInt();
    seq.resize(N);
    for (int i = 0; i < N; i++) {
        seq[i] = inf.readInt();
    }

    readAns(ans);
    readAns(ouf);
    quitf(_ok, "correct");
}
