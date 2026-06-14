#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300, "M");
    inf.readSpace();
    int l = inf.readInt(1, 300, "L");
    inf.readEoln();

    vector<int> x = inf.readInts(n, 1, 3, "x_i");
    inf.readEoln();

    inf.readEof();
}
