#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

int n;
vector<long long> target;

int waveCoeff(int k) {
    k %= 4;
    if (k < 0) {
        k += 4;
    }
    if (k == 1) {
        return 1;
    }
    if (k == 3) {
        return -1;
    }
    return 0;
}

struct Answer {
    int count;
};

Answer readAnswer(InStream& stream) {
    int m = stream.readInt(0, n, "M");
    stream.readEoln();

    vector<array<long long, 4>> delta(n + 2);
    for (int j = 1; j <= m; ++j) {
        int x = stream.readInt(1, n, format("x[%d]", j).c_str());
        long long v = stream.readLong(1, 2000000000LL, format("v[%d]", j).c_str());
        int phi = stream.readInt(0, 3, format("phi[%d]", j).c_str());
        stream.readEoln();

        int xMod = x % 4;
        for (int residue = 0; residue < 4; ++residue) {
            int coeff = waveCoeff(residue - xMod - phi);
            if (coeff != 0) {
                delta[x][residue] += coeff * v;
            }
        }
    }
    stream.readEof();

    array<long long, 4> active{};
    for (int i = 1; i <= n; ++i) {
        for (int residue = 0; residue < 4; ++residue) {
            active[residue] += delta[i][residue];
        }
        int residue = i % 4;
        if (active[residue] != target[i]) {
            stream.quitf(_wa,
                         "claimed speakers produce y[%d]=%lld, expected %lld",
                         i,
                         active[residue],
                         target[i]);
        }
    }

    return {m};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000000, "N");
    target.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        target[i] = inf.readLong(-1000000000LL, 1000000000LL, format("y[%d]", i).c_str());
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.count > jury.count) {
        quitf(_wa,
              "participant uses %d speakers, jury uses %d",
              participant.count,
              jury.count);
    }
    if (participant.count < jury.count) {
        quitf(_fail,
              "participant found fewer speakers: participant=%d jury=%d",
              participant.count,
              jury.count);
    }

    quitf(_ok, "valid minimum speaker count %d", participant.count);
}
