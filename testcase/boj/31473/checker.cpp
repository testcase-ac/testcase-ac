#include "testlib.h"

using namespace std;

const long long LIMIT = 1000000;

long long sumA;
long long sumB;

struct Answer {
    long long a;
    long long b;
    long long value;
};

Answer readAnswer(InStream& stream) {
    long long a = stream.readLong(-LIMIT, LIMIT, "a");
    long long b = stream.readLong(-LIMIT, LIMIT, "b");
    stream.readEoln();
    stream.readEof();

    if (a == 0) {
        stream.quitf(_wa, "a must be nonzero");
    }
    if (b == 0) {
        stream.quitf(_wa, "b must be nonzero");
    }

    long long value = llabs(a * sumA - b * sumB);
    return {a, b, value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    for (int i = 0; i < n; ++i) {
        sumA += inf.readInt();
    }
    for (int i = 0; i < n; ++i) {
        sumB += inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_fail,
              "participant found better answer: jury=(%lld, %lld) value=%lld, participant=(%lld, %lld) value=%lld",
              jury.a,
              jury.b,
              jury.value,
              participant.a,
              participant.b,
              participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_wa,
              "answer is not optimal enough: jury value=%lld, participant value=%lld",
              jury.value,
              participant.value);
    }

    quitf(_ok, "answer value=%lld", participant.value);
}
