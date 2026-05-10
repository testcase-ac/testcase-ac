#include "testlib.h"
#include <vector>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read C, D, M
    int C = inf.readInt(1, 50, "C");
    inf.readSpace();
    int D = inf.readInt(2, 10, "D");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readEoln();

    // Read C lines, each with D integers in [1,1000]
    for (int i = 0; i < C; ++i) {
        vector<int> prices = inf.readInts(D, 1, 1000, "price");
        inf.readEoln();
    }

    inf.readEof();
}
