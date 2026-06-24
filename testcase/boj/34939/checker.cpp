#include "testlib.h"

#include <vector>

using namespace std;

const int REQUIRED_N = 100000;
const long long REQUIRED_SUM = 29913857;

struct Claim {
    long long totalLength;
};

Claim readClaim(InStream& stream, int n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        a[i] = stream.readInt(0, n, format("A[%d]", i).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after A[%d]", n);
    }

    long long totalLength = 0;
    for (int marble = 1; marble <= n && totalLength < REQUIRED_SUM; ++marble) {
        int position = 1;
        ++totalLength;

        while (a[position] > 0 && position + a[position] <= n) {
            int nextPosition = position + a[position];
            --a[position];
            position = nextPosition;
            ++totalLength;

            if (totalLength >= REQUIRED_SUM) {
                break;
            }
        }

        if (totalLength >= REQUIRED_SUM) {
            break;
        }
        --a[position];
    }

    return {totalLength};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    if (n != REQUIRED_N) {
        quitf(_fail, "expected input N=%d, found N=%d", REQUIRED_N, n);
    }

    Claim jury = readClaim(ans, n);
    if (jury.totalLength < REQUIRED_SUM) {
        quitf(_fail,
              "jury output total length is too small: jury=%lld required=%lld",
              jury.totalLength,
              REQUIRED_SUM);
    }

    Claim participant = readClaim(ouf, n);
    if (participant.totalLength < REQUIRED_SUM) {
        quitf(_wa,
              "total length is too small: participant=%lld required=%lld",
              participant.totalLength,
              REQUIRED_SUM);
    }

    quitf(_ok, "total length is at least %lld", REQUIRED_SUM);
}
