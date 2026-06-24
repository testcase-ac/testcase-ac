#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int n;
vector<int> initialPermutation;

struct Answer {
    long long cost;
};

Answer readAnswer(InStream& stream, bool jury) {
    TResult invalid = jury ? _fail : _wa;

    int q = stream.readInt(0, 10000, "Q");
    vector<int> permutation = initialPermutation;
    long long cost = 0;

    for (int i = 0; i < q; ++i) {
        int l = stream.readInt(1, n, format("l[%d]", i + 1).c_str());
        int r = stream.readInt(1, n, format("r[%d]", i + 1).c_str());
        if (l > r) {
            stream.quitf(invalid, "operation %d has l=%d greater than r=%d", i + 1, l, r);
        }

        reverse(permutation.begin() + l, permutation.begin() + r + 1);
        cost += (r - l) % 2;
    }

    if (!stream.seekEof()) {
        stream.quitf(invalid, "extra output after %d operation(s)", q);
    }

    for (int i = 1; i <= n; ++i) {
        if (permutation[i] != i) {
            stream.quitf(invalid,
                         "operations do not sort the permutation: position %d has %d",
                         i,
                         permutation[i]);
        }
    }

    return {cost};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 5000, "N");
    initialPermutation.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        initialPermutation[i] = inf.readInt(1, n, format("P[%d]", i).c_str());
    }

    Answer jury = readAnswer(ans, true);
    Answer participant = readAnswer(ouf, false);

    if (participant.cost > jury.cost) {
        quitf(_wa,
              "participant cost %lld is greater than jury cost %lld",
              participant.cost,
              jury.cost);
    }
    if (participant.cost < jury.cost) {
        quitf(_fail,
              "participant found a better cost: participant=%lld jury=%lld",
              participant.cost,
              jury.cost);
    }

    quitf(_ok, "cost=%lld", participant.cost);
}
