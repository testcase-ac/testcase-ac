#include "testlib.h"

#include <vector>

using namespace std;

struct Clue {
    int l;
    int r;
    int x;
};

struct Answer {
    bool impossible;
    vector<long long> values;
};

int n, m;
vector<Clue> clues;

Answer readAnswer(InStream& stream) {
    long long first = stream.readLong();
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}};
    }

    vector<long long> values(n);
    if (first < 0 || first > 2000000000LL) {
        stream.quitf(_wa, "a[1]=%lld is outside [0, 2000000000]", first);
    }
    values[0] = first;

    for (int i = 1; i < n; ++i) {
        values[i] = stream.readLong(0LL, 2000000000LL, format("a[%d]", i + 1));
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after array");
    }

    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] ^ values[i];
    }
    for (int i = 0; i < m; ++i) {
        long long got = pref[clues[i].r] ^ pref[clues[i].l - 1];
        if (got != clues[i].x) {
            stream.quitf(_wa,
                         "clue %d is not satisfied: xor[%d,%d]=%lld, expected %d",
                         i + 1,
                         clues[i].l,
                         clues[i].r,
                         got,
                         clues[i].x);
        }
    }

    return {false, values};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    clues.resize(m);
    for (int i = 0; i < m; ++i) {
        clues[i].l = inf.readInt();
        clues[i].r = inf.readInt();
        clues[i].x = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "jury claims impossible, but participant provided a valid array");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible, but jury provided a valid array");
    }

    quitf(_ok, "participant provided a valid array");
}
