#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int n, m;
vector<int> initialS, xSwaps, ySwaps;

struct Answer {
    int rounds;
};

bool isSortedPermutation(const vector<int>& s) {
    for (int i = 0; i < n; ++i) {
        if (s[i] != i) {
            return false;
        }
    }
    return true;
}

Answer readAnswer(InStream& stream) {
    int rounds = stream.readInt(0, m, "R");
    stream.readEoln();

    vector<int> s = initialS;
    for (int i = 0; i < rounds; ++i) {
        int p = stream.readInt(0, n - 1, format("P[%d]", i).c_str());
        stream.readSpace();
        int q = stream.readInt(0, n - 1, format("Q[%d]", i).c_str());
        stream.readEoln();

        swap(s[xSwaps[i]], s[ySwaps[i]]);
        swap(s[p], s[q]);
    }

    stream.readEof();

    if (!isSortedPermutation(s)) {
        stream.quitf(_wa, "sequence is not sorted after %d rounds", rounds);
    }

    return {rounds};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initialS = inf.readInts(n);
    m = inf.readInt();

    xSwaps.resize(m);
    ySwaps.resize(m);
    for (int i = 0; i < m; ++i) {
        xSwaps[i] = inf.readInt();
        ySwaps[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok, "sorted in %d rounds; jury used %d rounds", participant.rounds, jury.rounds);
}
