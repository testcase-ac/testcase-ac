#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: n, w, L
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int w = inf.readInt(1, 100, "w");
    inf.readSpace();
    int L = inf.readInt(10, 1000, "L");
    inf.readEoln();

    // Read second line: weights of the n trucks
    vector<int> a = inf.readInts(n, 1, 10, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
