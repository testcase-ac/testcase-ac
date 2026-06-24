#include "testlib.h"

using namespace std;

int m, seed, x1, x2;

struct Answer {
    int a;
    int c;
};

Answer readAnswer(InStream& stream) {
    int a = stream.readInt(0, m - 1, "a");
    int c = stream.readInt(0, m - 1, "c");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after a and c");
    }

    if ((1LL * a * seed + c) % m != x1) {
        stream.quitf(_wa, "a=%d c=%d gives X_1=%lld instead of %d",
                     a, c, (1LL * a * seed + c) % m, x1);
    }
    if ((1LL * a * x1 + c) % m != x2) {
        stream.quitf(_wa, "a=%d c=%d gives X_2=%lld instead of %d",
                     a, c, (1LL * a * x1 + c) % m, x2);
    }

    return {a, c};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    m = inf.readInt();
    seed = inf.readInt();
    x1 = inf.readInt();
    x2 = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok, "valid answer a=%d c=%d; jury a=%d c=%d",
          participant.a, participant.c, jury.a, jury.c);
}
