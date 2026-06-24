#include "testlib.h"

using namespace std;

long long n;
long long a;
long long pa;
long long b;
long long pb;

struct Answer {
    long long x;
    long long y;
    long long value;
};

Answer readAnswer(InStream& stream) {
    long long x = stream.readLong(0, n, "tank count");
    long long y = stream.readLong(0, n, "dealer count");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after hire counts");
    }

    long long cost = pa * x + pb * y;
    if (cost > n) {
        stream.quitf(_wa, "cost exceeds budget: cost=%lld budget=%lld", cost, n);
    }

    return {x, y, a * x + b * y};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong();
    a = inf.readLong();
    pa = inf.readLong();
    b = inf.readLong();
    pb = inf.readLong();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_wa,
              "jury has better answer: jury=(%lld,%lld) value=%lld participant=(%lld,%lld) value=%lld",
              jury.x,
              jury.y,
              jury.value,
              participant.x,
              participant.y,
              participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail,
              "participant found better answer: jury=(%lld,%lld) value=%lld participant=(%lld,%lld) value=%lld",
              jury.x,
              jury.y,
              jury.value,
              participant.x,
              participant.y,
              participant.value);
    }

    quitf(_ok, "answer value=%lld", participant.value);
}
