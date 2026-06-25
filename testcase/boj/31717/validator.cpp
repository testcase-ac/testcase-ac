#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 200000, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, m, "A_i");
    }
    inf.readEoln();

    long long totalLength = 0;
    for (int i = 1; i <= m; ++i) {
        string top = inf.readToken("[.#]{1,500000}", "S_i1");
        inf.readEoln();
        string bottom = inf.readToken("[.#]{1,500000}", "S_i2");
        inf.readEoln();

        ensuref(top.size() == bottom.size(),
                "sample track %d rows have different lengths: %d and %d",
                i, static_cast<int>(top.size()), static_cast<int>(bottom.size()));
        totalLength += static_cast<long long>(top.size());
        ensuref(totalLength <= 500000,
                "sum of N_i exceeds 500000 after track %d: %lld",
                i, totalLength);
    }

    inf.readEof();
    return 0;
}
