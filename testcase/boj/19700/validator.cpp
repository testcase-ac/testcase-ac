#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // 2. Prepare to check uniqueness of heights
    set<int> heights;

    // 3. Read N lines of h_i, k_i
    for (int i = 0; i < N; ++i) {
        int h_i = inf.readInt(1, 500000, "h_i");
        inf.readSpace();
        int k_i = inf.readInt(1, N, "k_i");
        inf.readEoln();

        // Check uniqueness of h_i
        ensuref(heights.insert(h_i).second, "Height h_i=%d is not unique (duplicate at line %d)", h_i, i+2);
    }

    inf.readEof();
}
