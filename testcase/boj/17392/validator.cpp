#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 998, "N");
    inf.readSpace();
    int m = inf.readInt(n + 1, 999, "M");
    inf.readEoln();

    if (n == 0) {
        inf.readEoln();
    } else {
        vector<int> h = inf.readInts(n, 1, 99, "H_i");
        (void)h;
        inf.readEoln();
    }

    inf.readEof();
}
