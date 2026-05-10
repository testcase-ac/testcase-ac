#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 100, "N");
    inf.readSpace();
    int M = inf.readInt(3, 100, "M");
    inf.readSpace();
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    int gramCount = 0;
    int startVal = -1, endVal = -1;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            string name = "a[" + to_string(i) + "][" + to_string(j) + "]";
            int v = inf.readInt(0, 2, name.c_str());
            if (j < M) inf.readSpace(); else inf.readEoln();

            if (v == 2) ++gramCount;
            if (i == 1 && j == 1) startVal = v;
            if (i == N && j == M) endVal = v;
        }
    }

    ensuref(gramCount == 1, "There must be exactly one Gram cell with value 2, but found %d.", gramCount);
    ensuref(startVal == 0, "Cell (1,1) must be 0, but got %d.", startVal);
    ensuref(endVal == 0, "Cell (%d,%d) must be 0, but got %d.", N, M, endVal);

    inf.readEof();
}
