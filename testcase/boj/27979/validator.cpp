#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<int> w = inf.readInts(n, 1, 1000000, "w_i");
    inf.readEoln();

    inf.readEof();
}
