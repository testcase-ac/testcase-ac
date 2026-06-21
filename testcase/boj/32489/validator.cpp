#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<int> t = inf.readInts(n, -200000, 200000, "t_i");
    ensuref(t[0] == 0, "t_1 must be 0, found %d", t[0]);
    inf.readEoln();

    inf.readEof();
    return 0;
}
