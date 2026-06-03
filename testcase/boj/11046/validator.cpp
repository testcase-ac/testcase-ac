#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 100000, "a_i");
    inf.readEoln();

    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int s = inf.readInt(1, n, "s_i");
        inf.readSpace();
        int e = inf.readInt(s, n, "e_i");
        inf.readEoln();
    }

    inf.readEof();
}
