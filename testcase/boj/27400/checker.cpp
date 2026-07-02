#include "testlib.h"

#include <vector>
using namespace std;

struct Constraint {
    int l;
    int r;
    int k;
    int value;
};

struct Answer {
    bool impossible;
    vector<int> array;
};

int N, M;
vector<Constraint> constraints;

int kthSmallestBinaryValue(const vector<int>& a, const Constraint& c) {
    int zeros = 0;
    for (int i = c.l; i <= c.r; ++i) {
        zeros += (a[i] == 0);
    }
    return zeros >= c.k ? 0 : 1;
}

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, 1, "first output token");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}};
    }

    vector<int> a(N);
    a[0] = first;
    for (int i = 1; i < N; ++i) {
        a[i] = stream.readInt(0, 1, format("A[%d]", i).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after binary array");
    }

    for (int i = 0; i < M; ++i) {
        int actual = kthSmallestBinaryValue(a, constraints[i]);
        if (actual != constraints[i].value) {
            const Constraint& c = constraints[i];
            stream.quitf(_wa,
                         "constraint %d failed: range=[%d,%d], k=%d, expected=%d, found=%d",
                         i + 1,
                         c.l,
                         c.r,
                         c.k,
                         c.value,
                         actual);
        }
    }

    return {false, a};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    N = inf.readInt();
    M = inf.readInt();
    constraints.resize(M);
    for (int i = 0; i < M; ++i) {
        constraints[i].l = inf.readInt();
        constraints[i].r = inf.readInt();
        constraints[i].k = inf.readInt();
        constraints[i].value = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid array while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible while jury provides a valid array");
    }

    quitf(_ok, "valid binary array");
}
