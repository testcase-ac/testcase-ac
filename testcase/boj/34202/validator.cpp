#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 200000, "N");
    inf.readEoln();

    vector<long long> c = inf.readLongs(N - 1, 1LL, 1000000000000000000LL, "c_i");
    inf.readEoln();

    vector<long long> blocks(N);
    for (int i = 1; i < N; i++) {
        ensuref(c[i - 1] % 2 == 1, "c_%d must be odd", i);

        blocks[i] = (c[i - 1] + 1) / 2;
        long long maxBlocks = min(i, N - i);
        ensuref(blocks[i] <= maxBlocks, "c_%d creates too many prefix blocks", i);

        if (i > 1) {
            ensuref(abs(blocks[i] - blocks[i - 1]) <= 1,
                    "adjacent prefix block counts differ by more than 1");
        }
    }

    inf.readEof();
}
