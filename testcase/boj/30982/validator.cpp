#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    vector<int> q = inf.readInts(n, 1, 1000, "Q_i");
    inf.readEoln();

    int p = inf.readInt(1, n, "P");
    inf.readEoln();

    inf.readEof();
}
