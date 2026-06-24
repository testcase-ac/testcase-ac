#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

const long long MIN_SKILL = 1;
const long long MAX_SKILL = 1000000000LL;

int n, m;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    long long first = stream.readLong(-1, MAX_SKILL, "answer[1]");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }
    if (first < MIN_SKILL) {
        stream.quitf(_wa, "skill value must be at least 1, found %lld", first);
    }

    vector<long long> a(n), b(m);
    set<long long> used;
    long long sumA = 0;
    long long sumB = 0;

    a[0] = first;
    used.insert(first);
    sumA += first;

    for (int i = 1; i < n; ++i) {
        stream.readSpace();
        a[i] = stream.readLong(MIN_SKILL, MAX_SKILL, format("a[%d]", i + 1).c_str());
        if (!used.insert(a[i]).second) {
            stream.quitf(_wa, "skill value %lld is repeated", a[i]);
        }
        sumA += a[i];
    }
    stream.readEoln();

    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        b[i] = stream.readLong(MIN_SKILL, MAX_SKILL, format("b[%d]", i + 1).c_str());
        if (!used.insert(b[i]).second) {
            stream.quitf(_wa, "skill value %lld is repeated", b[i]);
        }
        sumB += b[i];
    }
    stream.readEoln();
    stream.readEof();

    bool rioAnimeWins = sumA * m > sumB * n;

    long long animePairWins = 0;
    for (long long x : a) {
        for (long long y : b) {
            if (x > y) {
                ++animePairWins;
            }
        }
    }
    long long normalPairWins = 1LL * n * m - animePairWins;
    bool rikuAnimeWins = animePairWins > normalPairWins;

    if (rioAnimeWins == rikuAnimeWins) {
        stream.quitf(_wa,
                     "Rio and Riku both choose %s",
                     rioAnimeWins ? "anime" : "normal");
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant provided a valid witness while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury provides a valid witness, but participant reports impossible");
    }

    quitf(_ok, "valid witness");
}
