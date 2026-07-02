#include "testlib.h"

#include <vector>

using namespace std;

int n;
long long k;
vector<long long> prefix;

struct Answer {
    int length;
    int start;
};

Answer readAnswer(InStream& stream) {
    int length = stream.readInt(0, n, "length");

    if (length == 0) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after zero answer");
        }
        return {0, 0};
    }

    int start = stream.readInt(1, n, "start");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (start + length - 1 > n) {
        stream.quitf(_wa, "segment [%d, %d] is outside 1..%d", start, start + length - 1, n);
    }

    long long sum = prefix[start + length - 1] - prefix[start - 1];
    long long expected = k * length;
    if (sum != expected) {
        stream.quitf(_wa,
                     "segment [%d, %d] has sum %lld, expected %lld",
                     start,
                     start + length - 1,
                     sum,
                     expected);
    }

    return {length, start};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readLong();

    prefix.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        long long ai = inf.readLong();
        prefix[i] = prefix[i - 1] + ai;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.length < jury.length) {
        quitf(_wa,
              "participant length %d is worse than jury length %d",
              participant.length,
              jury.length);
    }
    if (participant.length > jury.length) {
        quitf(_fail,
              "participant length %d is better than jury length %d",
              participant.length,
              jury.length);
    }

    quitf(_ok, "length %d", participant.length);
}
