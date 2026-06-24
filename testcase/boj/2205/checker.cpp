#include "testlib.h"

#include <vector>

using namespace std;

int n;

bool isPowerOfTwo(int value) {
    return value > 0 && (value & (value - 1)) == 0;
}

void readAnswer(InStream& stream) {
    vector<int> used(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int y = stream.readInt(1, n, format("tin[%d]", i).c_str());
        stream.readEoln();

        if (used[y]) {
            stream.quitf(_wa, "tin mass %d is used more than once", y);
        }
        used[y] = 1;

        if (!isPowerOfTwo(i + y)) {
            stream.quitf(_wa, "lead mass %d and tin mass %d sum to %d, not a power of two",
                         i, y, i + y);
        }
    }

    stream.readEof();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 10000, "n");

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid construction for n=%d", n);
}
