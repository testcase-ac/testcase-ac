#include "testlib.h"

using namespace std;

long long A, B;

struct Answer {
    long long x;
    long long y;
    int distance;
};

int hammingDistance(long long x, long long y) {
    return __builtin_popcountll(static_cast<unsigned long long>(x ^ y));
}

Answer readAnswer(InStream& stream) {
    long long x = stream.readLong(A, B, "first number");
    long long y = stream.readLong(A, B, "second number");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the two numbers");
    }
    return {x, y, hammingDistance(x, y)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    A = inf.readLong();
    B = inf.readLong();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.distance < jury.distance) {
        quitf(_wa,
              "jury has better Hamming distance: jury=%d (%lld, %lld), participant=%d (%lld, %lld)",
              jury.distance, jury.x, jury.y, participant.distance, participant.x, participant.y);
    }
    if (participant.distance > jury.distance) {
        quitf(_fail,
              "participant found better Hamming distance: jury=%d (%lld, %lld), participant=%d (%lld, %lld)",
              jury.distance, jury.x, jury.y, participant.distance, participant.x, participant.y);
    }

    quitf(_ok, "Hamming distance %d", participant.distance);
}
