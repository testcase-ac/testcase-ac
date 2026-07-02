#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(0, n, "K");
    inf.readEoln();

    vector<int> a = inf.readInts(n, -1000000, 1000000, "A_i");
    inf.readEoln();

    vector<int> b = inf.readInts(n, -1000000, 1000000, "B_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
