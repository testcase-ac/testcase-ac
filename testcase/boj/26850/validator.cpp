#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    vector<int> s = inf.readInts(m, 1, 1000000, "S_i");
    inf.readEoln();

    // CHECK: The statement calls S a set, but official samples contain a
    // duplicate value, so duplicate S_i values are accepted.
    (void)n;
    (void)s;

    inf.readEof();
}
