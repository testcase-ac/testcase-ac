#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // CHECK: The statement does not require the bought product numbers to be distinct.
    vector<int> a = inf.readInts(m, 2, n, "A_i");
    inf.readEoln();

    inf.readEof();
}
