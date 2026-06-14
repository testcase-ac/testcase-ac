#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 200000, "M");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 2, 500000, "A_i");
    inf.readEoln();

    for (int plan = 1; plan <= m; ++plan) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(i, n, "j");
        inf.readEoln();
    }

    inf.readEof();
}
