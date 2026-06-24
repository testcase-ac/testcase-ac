#include "testlib.h"

using namespace std;

long long m;
long long seed_value;
long long x1;
long long x2;

struct Answer {
    long long a;
    long long c;
};

Answer readAnswer(InStream& stream) {
    long long a = stream.readLong(0, m - 1, "a");
    long long c = stream.readLong(0, m - 1, "c");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after a and c");
    }

    if ((a * seed_value + c) % m != x1) {
        stream.quitf(_wa,
                     "a=%lld c=%lld produces X_1=%lld, expected %lld",
                     a,
                     c,
                     (a * seed_value + c) % m,
                     x1);
    }
    if ((a * x1 + c) % m != x2) {
        stream.quitf(_wa,
                     "a=%lld c=%lld produces X_2=%lld, expected %lld",
                     a,
                     c,
                     (a * x1 + c) % m,
                     x2);
    }

    return {a, c};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    m = inf.readLong();
    seed_value = inf.readLong();
    x1 = inf.readLong();
    x2 = inf.readLong();

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid parameters");
}
