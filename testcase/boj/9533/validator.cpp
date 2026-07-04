#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "N");
    inf.readEoln();

    vector<int> lengths = inf.readInts(n, 1, 50, "L_i");
    inf.readEoln();
    inf.readEof();

    __int128_t kraft = 0;
    for (int length : lengths) {
        kraft += static_cast<__int128_t>(1) << (50 - length);
    }

    // The statement guarantees that at least one tree exists for these lengths.
    ensuref(kraft == (static_cast<__int128_t>(1) << 50),
            "code lengths must form a full binary tree");
}
