#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10, "N");
    inf.readSpace();
    int k = inf.readInt(0, n - 1, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int t = inf.readInt(0, 1000, "T_ij");
            ensuref(i != j || t == 0, "diagonal entry T_%d_%d must be 0, got %d", i, j, t);

            if (j + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
    return 0;
}
