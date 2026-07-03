#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    while (true) {
        int n = inf.readInt(0, 50, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        // CHECK: non-terminating instances need at least two indices to have poly-polygonal outputs.
        ensuref(n >= 2, "non-terminating instance has fewer than two polygonal indices: %d", n);

        vector<int> indices;
        indices.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            int k = inf.readInt(3, 1000, "k_i");
            if (!indices.empty()) {
                ensuref(indices.back() < k, "indices must be distinct and increasing at position %d", i + 1);
            }
            indices.push_back(k);
        }
        inf.readEoln();

        inf.readInt(1, 10000, "s");
        inf.readEoln();
    }

    inf.readEof();
}
