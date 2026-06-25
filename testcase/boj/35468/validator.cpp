#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    vector<int> b = inf.readInts(n, 0, 1, "B_i");
    inf.readEoln();

    inf.readEof();
}
