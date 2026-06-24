#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

void readAnswer(InStream& stream, int n) {
    vector<int> a(n);
    vector<int> seen(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        a[i] = stream.readInt(1, n, format("A[%d]", i + 1).c_str());
        if (seen[a[i]]) {
            stream.quitf(_wa, "value %d appears more than once", a[i]);
        }
        seen[a[i]] = 1;
    }

    for (int i = 1; i + 1 < n; ++i) {
        int prevDiff = abs(a[i] - a[i - 1]);
        int curDiff = abs(a[i + 1] - a[i]);
        if (prevDiff >= curDiff) {
            stream.quitf(_wa,
                         "adjacent differences are not strictly increasing at positions %d and %d: %d >= %d",
                         i + 1,
                         i + 2,
                         prevDiff,
                         curDiff);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(3, 200000, "N");
    readAnswer(ans, n);
    readAnswer(ouf, n);

    quitf(_ok, "valid INU permutation");
}
