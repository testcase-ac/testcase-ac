#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "N");
    inf.readEoln();

    vector<int> lengths = inf.readInts(n, 1, 1000000, "L_i");
    (void)lengths;
    inf.readEoln();

    inf.readEof();
}
