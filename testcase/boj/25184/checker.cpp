#include "testlib.h"

#include <vector>

using namespace std;

int n;

vector<int> readSequence(InStream& stream) {
    vector<int> sequence(n);
    vector<int> seen(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        sequence[i] = stream.readInt(1, n, format("a[%d]", i + 1).c_str());
        if (seen[sequence[i]]) {
            stream.quitf(_wa, "value %d appears more than once", sequence[i]);
        }
        seen[sequence[i]] = 1;
    }

    stream.readEoln();
    stream.readEof();

    int requiredDiff = n / 2;
    for (int i = 0; i + 1 < n; ++i) {
        int diff = abs(sequence[i] - sequence[i + 1]);
        if (diff < requiredDiff) {
            stream.quitf(_wa,
                         "adjacent values a[%d]=%d and a[%d]=%d differ by %d, less than %d",
                         i + 1,
                         sequence[i],
                         i + 2,
                         sequence[i + 1],
                         diff,
                         requiredDiff);
        }
    }

    return sequence;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 5000, "N");
    inf.readEoln();
    inf.readEof();

    readSequence(ans);
    readSequence(ouf);

    quitf(_ok, "valid equal-difference sequence of length %d", n);
}
