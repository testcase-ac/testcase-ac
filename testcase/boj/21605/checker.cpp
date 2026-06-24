#include "testlib.h"

#include <string>
using namespace std;

int n;

struct Answer {
    long long beauty;
};

int readValue(InStream& stream, TResult verdict, int index) {
    string token = stream.readToken("-1|1", format("A[%d]", index).c_str());
    if (token == "1") {
        return 1;
    }
    if (token == "-1") {
        return -1;
    }
    stream.quitf(verdict, "A[%d] must be -1 or 1, found '%s'", index, token.c_str());
    return 0;
}

Answer readAnswer(InStream& stream, TResult verdict) {
    int ones = 0;
    int minusOnes = 0;
    long long beauty = 0;

    for (int i = 1; i <= n; ++i) {
        int odd = readValue(stream, verdict, 2 * i - 1);
        int even = readValue(stream, verdict, 2 * i);

        ones += (odd == 1) + (even == 1);
        minusOnes += (odd == -1) + (even == -1);
        beauty = beauty * odd + even;
    }

    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after %d sequence elements", 2 * n);
    }
    if (ones != n || minusOnes != n) {
        stream.quitf(verdict,
                     "sequence must contain exactly %d ones and %d minus ones, found %d and %d",
                     n,
                     n,
                     ones,
                     minusOnes);
    }

    return {beauty};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100000, "N");

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (participant.beauty < jury.beauty) {
        quitf(_wa,
              "jury has better beauty: jury=%lld participant=%lld",
              jury.beauty,
              participant.beauty);
    }
    if (participant.beauty > jury.beauty) {
        quitf(_fail,
              "participant found better beauty: jury=%lld participant=%lld",
              jury.beauty,
              participant.beauty);
    }

    quitf(_ok, "beauty=%lld", participant.beauty);
}
