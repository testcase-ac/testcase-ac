#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, -10000, 10000, "a_i");
    inf.readEoln();

    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        // CHECK: A and B are described as prefix endpoint positions but no explicit bound is written.
        inf.readInt(1, n, "A");
        inf.readSpace();
        inf.readInt(1, n, "B");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
