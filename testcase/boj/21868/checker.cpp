#include "testlib.h"

using namespace std;

const long long LIMIT_BOUND = 4000000000000000000LL;

struct Answer {
    long long limit;
    bool noFiniteDelta;
    long long numerator;
    long long denominator;
};

Answer readAnswer(InStream& stream) {
    Answer result{};

    result.limit = stream.readLong(-LIMIT_BOUND, LIMIT_BOUND, "L");
    stream.readEoln();

    result.numerator =
        stream.readLong(0LL, 100000000LL, "delta numerator");
    stream.readSpace();
    result.denominator =
        stream.readLong(0LL, 100000000LL, "delta denominator");
    stream.readEoln();
    stream.readEof();

    result.noFiniteDelta = result.numerator == 0 && result.denominator == 0;
    if (!result.noFiniteDelta &&
        (result.numerator == 0 || result.denominator == 0)) {
        stream.quitf(_wa,
                     "delta must be 0 0 or positive fraction, found %lld %lld",
                     result.numerator,
                     result.denominator);
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.limit != jury.limit) {
        quitf(_wa,
              "expected L=%lld, found L=%lld",
              jury.limit,
              participant.limit);
    }

    if (participant.noFiniteDelta != jury.noFiniteDelta) {
        quitf(_wa,
              "expected delta %s, found %s",
              jury.noFiniteDelta ? "0 0" : "as a positive fraction",
              participant.noFiniteDelta ? "0 0" : "a positive fraction");
    }

    if (jury.noFiniteDelta) {
        quitf(_ok, "L=%lld and delta=0 0", participant.limit);
    }

    __int128 left = (__int128)participant.numerator * jury.denominator;
    __int128 right = (__int128)jury.numerator * participant.denominator;
    if (left != right) {
        quitf(_wa,
              "expected delta %lld/%lld, found %lld/%lld",
              jury.numerator,
              jury.denominator,
              participant.numerator,
              participant.denominator);
    }

    quitf(_ok,
          "L=%lld and delta=%lld/%lld",
          participant.limit,
          participant.numerator,
          participant.denominator);
}
