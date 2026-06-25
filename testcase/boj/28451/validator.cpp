#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int l = inf.readInt(1, 100000, "L");
    inf.readEoln();

    inf.readInt(1, 10, "A");
    inf.readSpace();
    inf.readInt(1, 100000, "B");
    inf.readEoln();

    vector<int> d = inf.readInts(n, 1, l, "d_i");
    inf.readEoln();

    inf.readInts(n, 1, 100000, "h_i");
    inf.readEoln();

    inf.readEof();
}
