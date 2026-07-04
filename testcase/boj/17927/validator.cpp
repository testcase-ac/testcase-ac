#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int l = inf.readInt(1, 1000000, "L");
    inf.readEoln();

    vector<int> g = inf.readInts(l, 1, n, "g_i");
    (void)g;
    inf.readEoln();

    inf.readEof();
}
