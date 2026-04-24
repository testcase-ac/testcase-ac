#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read header: n, l, m, W
    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int l = inf.readInt(2, 3000, "l");
    ensuref(n >= l, "n (%d) must be at least l (%d)", n, l);
    inf.readSpace();
    int m = inf.readInt(2, 100, "m");
    inf.readSpace();
    long long maxW = 10000LL * l * m;
    long long W = inf.readLong(0LL, maxW, "W");
    inf.readEoln();

    // Read the path grid T: m rows, each with n integers
    for (int i = 1; i <= m; i++) {
        vector<int> rowT = inf.readInts(n, 0, 100, "T");
        inf.readEoln();
    }

    // Read the telescope grid P: m rows, each with l integers
    for (int i = 1; i <= m; i++) {
        vector<int> rowP = inf.readInts(l, 0, 100, "P");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
