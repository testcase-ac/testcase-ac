#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readEoln();

    vector<int> c = inf.readInts(n, 1, 100000, "c_i");
    inf.readEoln();

    vector<int> w = inf.readInts(m, 1, 100000, "w_i");
    inf.readEoln();

    inf.readEof();
}
