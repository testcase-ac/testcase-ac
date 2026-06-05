#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 1000, "K");
    inf.readEoln();

    ensuref(k % 2 == 0, "K must be even, got %d", k);

    vector<int> berries = inf.readInts(n, 1, 1000, "B_i");
    inf.readEoln();

    inf.readEof();
}
