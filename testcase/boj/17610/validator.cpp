#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // k: number of weights
    int k = inf.readInt(3, 13, "k");
    inf.readEoln();

    // read the k weights
    vector<int> g = inf.readInts(k, 1, 200000, "g");
    inf.readEoln();

    // check all weights are distinct
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            ensuref(g[i] != g[j],
                    "Duplicate weights detected at positions %d and %d: both are %d",
                    i + 1, j + 1, g[i]);
        }
    }

    inf.readEof();
    return 0;
}
