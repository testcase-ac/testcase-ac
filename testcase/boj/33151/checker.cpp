#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

int n;
long long k;

struct Claim {
    bool impossible;
};

long long readCell(InStream& stream, int row, int col) {
    return stream.readLong(0LL, k, format("grid[%d][%d]", row + 1, col + 1).c_str());
}

Claim readClaim(InStream& stream) {
    long long first = stream.readLong(-1LL, k, "first output value");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<long long> prev(n), cur(n);
    long long sum = first;
    cur[0] = first;

    for (int j = 1; j < n; ++j) {
        stream.readSpace();
        cur[j] = readCell(stream, 0, j);
        sum += cur[j];
        if (llabs(cur[j] - cur[j - 1]) != 1) {
            stream.quitf(_wa,
                         "adjacent cells (1,%d) and (1,%d) differ by %lld, not 1",
                         j, j + 1, llabs(cur[j] - cur[j - 1]));
        }
    }
    stream.readEoln();
    prev.swap(cur);

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                stream.readSpace();
            }
            cur[j] = readCell(stream, i, j);
            sum += cur[j];
            if (sum > k) {
                stream.quitf(_wa, "grid sum exceeds K: partial sum is %lld, K is %lld", sum, k);
            }
            if (llabs(cur[j] - prev[j]) != 1) {
                stream.quitf(_wa,
                             "adjacent cells (%d,%d) and (%d,%d) differ by %lld, not 1",
                             i, j + 1, i + 1, j + 1, llabs(cur[j] - prev[j]));
            }
            if (j > 0 && llabs(cur[j] - cur[j - 1]) != 1) {
                stream.quitf(_wa,
                             "adjacent cells (%d,%d) and (%d,%d) differ by %lld, not 1",
                             i + 1, j, i + 1, j + 1, llabs(cur[j] - cur[j - 1]));
            }
        }
        stream.readEoln();
        prev.swap(cur);
    }

    stream.readEof();

    if (sum != k) {
        stream.quitf(_wa, "grid sum is %lld, expected K=%lld", sum, k);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readLong();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant provided a valid grid while jury output is -1");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible while jury provides a valid grid");
    }

    quitf(_ok, "valid grid");
}
