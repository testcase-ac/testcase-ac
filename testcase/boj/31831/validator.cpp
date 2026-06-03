#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000000000, "M");
    inf.readEoln();

    vector<int> a = inf.readInts(n, -10000, 10000, "A_i");
    inf.readEoln();

    inf.readEof();
}
