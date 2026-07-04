#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    vector<int> z = inf.readInts(n, 0, 1000000, "z_i");
    inf.readEoln();

    vector<int> p = inf.readInts(m, 0, 1000000, "p_j");
    inf.readEoln();

    inf.readEof();
}
