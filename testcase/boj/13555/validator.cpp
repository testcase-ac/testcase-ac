#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 50, "k");
    inf.readEoln();

    ensuref(k <= n, "k must not exceed n: k=%d, n=%d", k, n);

    vector<int> a = inf.readInts(n, 1, 100000, "a_i");
    inf.readEoln();

    inf.readEof();
}
