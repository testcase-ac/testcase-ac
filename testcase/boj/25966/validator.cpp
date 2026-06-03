#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 3000, "M");
    inf.readSpace();
    int q = inf.readInt(1, 1000000, "q");
    inf.readEoln();

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col) {
            if (col > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 10000, "A_ij");
        }
        inf.readEoln();
    }

    for (int query = 0; query < q; ++query) {
        int type = inf.readInt(0, 1, "query_type");
        inf.readSpace();

        if (type == 0) {
            inf.readInt(0, n - 1, "i");
            inf.readSpace();
            inf.readInt(0, m - 1, "j");
            inf.readSpace();
            inf.readInt(1, 10000, "k");
        } else {
            inf.readInt(0, n - 1, "i");
            inf.readSpace();
            inf.readInt(0, n - 1, "j");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
