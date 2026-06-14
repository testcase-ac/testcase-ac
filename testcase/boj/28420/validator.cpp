#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300, "N");
    inf.readSpace();
    int m = inf.readInt(2, 300, "M");
    inf.readEoln();

    int maxSize = min(n / 2, m / 2);
    int a = inf.readInt(1, maxSize, "a");
    inf.readSpace();
    int b = inf.readInt(1, maxSize, "b");
    inf.readSpace();
    int c = inf.readInt(1, maxSize, "c");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInts(m, 1, 20, "A_i_j");
        inf.readEoln();
    }

    inf.readEof();
}
