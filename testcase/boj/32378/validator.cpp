#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(0, n, "k");
    inf.readSpace();
    inf.readInt(1, 100, "s");
    inf.readEoln();

    vector<int> a = inf.readInts(n, -500, 500, "A_i");
    (void)a;
    (void)k;
    inf.readEoln();

    inf.readEof();
    return 0;
}
