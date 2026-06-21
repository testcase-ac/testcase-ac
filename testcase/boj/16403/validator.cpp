#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    inf.readInt(0, 1000, "A");
    inf.readSpace();
    inf.readInt(0, 100000, "B");
    inf.readEoln();

    vector<int> blocks = inf.readInts(n, 0, 10000, "block_i");
    inf.readEoln();

    inf.readEof();
}
