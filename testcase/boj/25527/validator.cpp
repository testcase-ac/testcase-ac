#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++datasets;
        setTestCase(datasets);
        ensuref(datasets <= 100, "too many datasets: %d", datasets);
        ensuref(3 <= n, "n must be at least 3, got %d", n);

        vector<int> v = inf.readInts(n, 0, 1000, "v_i");
        inf.readEoln();

        ensuref(v[0] == 0, "v_1 must be 0, got %d", v[0]);
        for (int i = 0; i + 1 < n; ++i) {
            ensuref(v[i] != v[i + 1],
                    "adjacent values must differ at indices %d and %d: %d",
                    i + 1, i + 2, v[i]);
        }
    }

    inf.readEof();
}
