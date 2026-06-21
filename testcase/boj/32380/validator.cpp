#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000, "U");
    inf.readSpace();
    inf.readInt(1, 1000000, "D");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, 1000000, "A_i");
    inf.readEoln();

    vector<int> b = inf.readInts(n, 0, 1000000, "B_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
