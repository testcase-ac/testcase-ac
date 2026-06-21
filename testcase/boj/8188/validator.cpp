#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int kMaxLength = 1000000;
    const int kMaxValue = 1000000;

    int m = inf.readInt(1, kMaxLength, "m");
    inf.readEoln();
    inf.readInts(m, 1, kMaxValue, "a_i");
    inf.readEoln();

    int n = inf.readInt(1, kMaxLength, "n");
    inf.readEoln();

    long long totalQueryLength = 0;
    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        int mi = inf.readInt(1, kMaxLength, "m_i");
        inf.readEoln();
        totalQueryLength += mi;
        ensuref(totalQueryLength <= kMaxLength,
                "total query length exceeds %d at sequence %d", kMaxLength, i);

        inf.readInts(mi, 1, kMaxValue, "b_i_j");
        inf.readEoln();
    }

    inf.readEof();
}
