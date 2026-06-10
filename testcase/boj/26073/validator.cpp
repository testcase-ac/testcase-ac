#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(-100000, 100000, "X_i");
        inf.readSpace();
        int y = inf.readInt(-100000, 100000, "Y_i");
        inf.readEoln();

        int k = inf.readInt(1, 32, "K_i");
        for (int j = 1; j <= k; ++j) {
            inf.readSpace();
            inf.readInt(1, 100000, "A_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
