#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readEoln();

    vector<int> s = inf.readInts(n, 1, 10000000, "S_i");
    inf.readEoln();

    inf.readEof();
}
