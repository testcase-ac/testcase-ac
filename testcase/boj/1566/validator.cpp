#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only gives the upper bound, but an array needs at least one row and one column.
    int n = inf.readInt(1, 18, "N");
    inf.readSpace();
    int m = inf.readInt(1, 18, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(-26, 35, "A_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
