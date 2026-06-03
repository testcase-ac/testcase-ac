#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 9, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readEoln();

    vector<int> h = inf.readInts(n, 1, 1000, "H_i");
    inf.readEoln();

    inf.readEof();
}
