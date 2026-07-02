#include "testlib.h"

#include <algorithm>
#include <numeric>

using namespace std;

struct Answer {
    long long x;
    long long y;
    long long diff;
};

long long a, b;
long long targetGcd, targetLcm;

long long lcmOf(long long x, long long y) {
    __int128 value = (__int128)(x / gcd(x, y)) * y;
    if (value > targetLcm) {
        return targetLcm + 1;
    }
    return (long long)value;
}

Answer readAnswer(InStream& stream) {
    long long x = stream.readLong(1, targetLcm, "x");
    long long y = stream.readLong(1, targetLcm, "y");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer pair");
    }

    if (x > y) {
        stream.quitf(_wa, "x=%lld is greater than y=%lld", x, y);
    }

    long long actualGcd = gcd(x, y);
    if (actualGcd != targetGcd) {
        stream.quitf(_wa, "gcd(%lld, %lld) is %lld, expected %lld", x, y, actualGcd, targetGcd);
    }

    long long actualLcm = lcmOf(x, y);
    if (actualLcm != targetLcm) {
        stream.quitf(_wa, "lcm(%lld, %lld) is %lld, expected %lld", x, y, actualLcm, targetLcm);
    }

    return {x, y, y - x};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    a = inf.readLong(1, 1000000000LL, "a");
    b = inf.readLong(1, 1000000000LL, "b");
    targetGcd = gcd(a, b);
    targetLcm = (a / targetGcd) * b;

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.diff > jury.diff) {
        quitf(_wa,
              "participant difference %lld is larger than jury difference %lld",
              participant.diff,
              jury.diff);
    }
    if (participant.diff < jury.diff) {
        quitf(_fail,
              "participant found a better pair (%lld, %lld) than jury pair (%lld, %lld)",
              participant.x,
              participant.y,
              jury.x,
              jury.y);
    }

    quitf(_ok, "valid pair (%lld, %lld) with minimum difference %lld", participant.x, participant.y, participant.diff);
}
