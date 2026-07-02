#include "testlib.h"

#include <set>

using namespace std;

const long long MAX_XOR = (1LL << 40) - 1;

long long l, r, k;

struct Answer {
    long long value;
};

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(0LL, MAX_XOR, "xor value");
    stream.readEoln();

    long long size = stream.readLong(1LL, k, "set size");
    stream.readEoln();

    set<long long> seen;
    long long actual = 0;
    for (long long i = 0; i < size; ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        long long x = stream.readLong(l, r, format("element[%lld]", i + 1).c_str());
        if (!seen.insert(x).second) {
            stream.quitf(_wa, "element %lld is repeated", x);
        }
        actual ^= x;
    }
    stream.readEoln();
    stream.readEof();

    if (actual != claimed) {
        stream.quitf(_wa, "claimed xor is %lld but selected elements xor to %lld", claimed, actual);
    }

    return {actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    l = inf.readLong();
    r = inf.readLong();
    k = inf.readLong();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value > jury.value) {
        quitf(_wa, "jury has better xor: jury=%lld participant=%lld", jury.value, participant.value);
    }
    if (participant.value < jury.value) {
        quitf(_fail, "participant found better xor: jury=%lld participant=%lld", jury.value, participant.value);
    }

    quitf(_ok, "xor=%lld", participant.value);
}
