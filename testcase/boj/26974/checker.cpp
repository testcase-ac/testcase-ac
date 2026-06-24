#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIM = 1000000000LL;

int n;
vector<vector<long long>> expectedRange;

struct Answer {
    vector<long long> a;
};

Answer readAnswer(InStream& stream) {
    Answer answer;
    answer.a.resize(n);

    for (int i = 0; i < n; ++i) {
        answer.a[i] = stream.readLong(-LIM, LIM, format("b[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d array values", n);
    }

    for (int l = 0; l < n; ++l) {
        long long mn = answer.a[l];
        long long mx = answer.a[l];
        for (int r = l; r < n; ++r) {
            mn = min(mn, answer.a[r]);
            mx = max(mx, answer.a[r]);
            long long got = mx - mn;
            if (got != expectedRange[l][r]) {
                stream.quitf(_wa,
                             "range mismatch for [%d, %d]: expected %lld, found %lld",
                             l + 1,
                             r + 1,
                             expectedRange[l][r],
                             got);
            }
        }
    }

    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    expectedRange.assign(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            expectedRange[i][j] = inf.readLong();
        }
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid reconstruction");
}
