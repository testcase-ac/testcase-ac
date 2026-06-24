#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<long long> firstSeq;
vector<long long> secondSeq;

struct Answer {
    int b;
    int e;
    long long value;
};

long long computeFuzziness(int b, int e) {
    long long result = 0;
    int len = n - b - e;
    for (int i = 0; i < len; ++i) {
        result += firstSeq[b + i] * secondSeq[n - e - 1 - i];
    }
    return result;
}

Answer readAnswer(InStream& stream) {
    int b = stream.readInt(0, n - 1, "B");
    int e = stream.readInt(0, n - 1, "E");
    stream.readEoln();

    if (b + e >= n) {
        stream.quitf(_wa, "B + E must be less than N, found B=%d E=%d N=%d", b, e, n);
    }

    long long claimed = stream.readLong(-4000000000000LL, 4000000000000LL, "fuzziness");
    stream.readEoln();
    stream.readEof();

    long long actual = computeFuzziness(b, e);
    if (claimed != actual) {
        stream.quitf(_wa,
                     "claimed fuzziness does not match B and E: B=%d E=%d claimed=%lld actual=%lld",
                     b,
                     e,
                     claimed,
                     actual);
    }

    return {b, e, actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    firstSeq.resize(n);
    secondSeq.resize(n);
    for (int i = 0; i < n; ++i) {
        firstSeq[i] = inf.readLong();
    }
    for (int i = 0; i < n; ++i) {
        secondSeq[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_wa,
              "participant answer is worse than jury answer: participant=%lld jury=%lld",
              participant.value,
              jury.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail,
              "participant found a better answer than jury: participant=%lld jury=%lld",
              participant.value,
              jury.value);
    }

    quitf(_ok, "answer=%lld B=%d E=%d", participant.value, participant.b, participant.e);
}
