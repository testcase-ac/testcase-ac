#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int p = inf.readInt(1, 100, "P");
    inf.readSpace();
    int q = inf.readInt(1, 100, "Q");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 100, "A_i");
    inf.readEoln();

    vector<int> b = inf.readInts(n, 1, 100, "B_i");
    inf.readEoln();

    inf.readEof();
}
