#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 1000000000, "K");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000000, "a_i");
    inf.readEoln();

    vector<int> b = inf.readInts(m, 1, 1000000000, "b_i");
    inf.readEoln();

    inf.readEof();
}
