#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 1000, "q");
    inf.readEoln();

    vector<int> a = inf.readInts(n, -10000, 10000, "a_i");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int l = inf.readInt(1, n, "q_l");
        inf.readSpace();
        int r = inf.readInt(l, n, "q_r");
        inf.readEoln();
    }

    inf.readEof();
}
