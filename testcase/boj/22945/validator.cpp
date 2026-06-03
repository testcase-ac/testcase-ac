#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<int> abilities = inf.readInts(n, 1, 10000, "x_i");
    (void)abilities;
    inf.readEoln();

    inf.readEof();
}
