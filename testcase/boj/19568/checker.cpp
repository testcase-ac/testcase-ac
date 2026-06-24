#include "testlib.h"

#include <vector>

using namespace std;

const int N = 30;
const int TARGET = 50000;
const int MAX_VALUE = 1000000;

struct Claim {
    bool coversAll;
    int coveredCount;
};

Claim readClaim(InStream& stream) {
    vector<vector<long long>> grid(N, vector<long long>(N));
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            grid[r][c] = stream.readInt(0, MAX_VALUE, format("cell[%d][%d]", r + 1, c + 1).c_str());
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after 30 by 30 grid");
    }

    vector<vector<long long>> prefix(N + 1, vector<long long>(N + 1, 0));
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            prefix[r + 1][c + 1] = prefix[r][c + 1] + prefix[r + 1][c] - prefix[r][c] + grid[r][c];
        }
    }

    vector<bool> covered(TARGET + 1, false);
    int coveredCount = 0;
    for (int top = 0; top < N; ++top) {
        for (int bottom = top; bottom < N; ++bottom) {
            for (int left = 0; left < N; ++left) {
                for (int right = left; right < N; ++right) {
                    long long sum = prefix[bottom + 1][right + 1] - prefix[top][right + 1] -
                                    prefix[bottom + 1][left] + prefix[top][left];
                    if (1 <= sum && sum <= TARGET && !covered[sum]) {
                        covered[sum] = true;
                        ++coveredCount;
                    }
                }
            }
        }
    }

    return {coveredCount == TARGET, coveredCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Claim jury = readClaim(ans);
    if (!jury.coversAll) {
        quitf(_fail, "jury grid covers only %d values in [1, %d]", jury.coveredCount, TARGET);
    }

    Claim participant = readClaim(ouf);
    if (!participant.coversAll) {
        quitf(_wa, "participant grid covers only %d values in [1, %d]", participant.coveredCount, TARGET);
    }

    quitf(_ok, "valid grid covers all values in [1, %d]", TARGET);
}
