#include "testlib.h"

#include <set>
#include <string>

using namespace std;

const long long MIN_N = -1000000000000LL;
const long long MAX_N = 1000000000000LL;
const long long MAX_X = 1000000000000LL;
const int MAX_K = 1000000;

long long targetN;

struct Answer {
    bool impossible;
    int k;
};

Answer readAnswer(InStream& stream) {
    long long first = stream.readLong(-1LL, (long long)MAX_K, "K");
    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        return {true, -1};
    }

    int k = (int)first;
    if (k < 1) {
        stream.quitf(_wa, "K must be positive or -1, found %d", k);
    }
    stream.readEoln();

    set<long long> used;
    __int128 sum = 0;
    for (int i = 0; i < k; ++i) {
        string sign = stream.readToken("[+-]", format("sign[%d]", i + 1).c_str());
        long long x = stream.readLong(1, MAX_X, format("X[%d]", i + 1).c_str());
        if (!used.insert(x).second) {
            stream.quitf(_wa, "X=%lld is used more than once", x);
        }

        __int128 square = (__int128)x * x;
        if (sign == "+") {
            sum += square;
        } else {
            sum -= square;
        }

        stream.readEoln();
    }
    stream.readEof();

    if (sum != targetN) {
        stream.quitf(_wa, "certificate sum does not match N");
    }

    return {false, k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    targetN = inf.readLong(MIN_N, MAX_N, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid certificate while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a certificate with K=%d, participant claims impossible", jury.k);
    }
    if (participant.k < jury.k) {
        quitf(_fail, "participant found better certificate: jury K=%d, participant K=%d", jury.k, participant.k);
    }
    if (participant.k > jury.k) {
        quitf(_wa, "jury has better certificate: jury K=%d, participant K=%d", jury.k, participant.k);
    }

    quitf(_ok, "valid certificate with K=%d", participant.k);
}
