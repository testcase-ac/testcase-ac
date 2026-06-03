#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 256, "N");
    inf.readSpace();
    int m = inf.readInt(1, 256, "M");
    inf.readSpace();
    inf.readInt(1, 1000000, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 50, "A_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
