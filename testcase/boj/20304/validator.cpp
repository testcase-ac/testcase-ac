#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 1000000, "N");
    inf.readEoln();

    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(0, n, "p_i");
    }
    inf.readEoln();

    inf.readEof();
}
