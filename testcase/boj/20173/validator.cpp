#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000000, "n");
    inf.readEoln();

    vector<int> d = inf.readInts(n, 0, n, "d_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
