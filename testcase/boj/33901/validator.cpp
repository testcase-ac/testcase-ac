#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n - 1, "M");
    inf.readSpace();
    inf.readInt(0, (1 << 17) - 1, "K");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, 100000, "A_i");
    inf.readEoln();

    inf.readEof();
}
