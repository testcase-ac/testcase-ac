#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 300000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int a_i = inf.readInt(0, n, "A_i");
        ensuref(a_i == 0 || a_i >= 2, "A_%d must be 0 or at least 2, got %d", i, a_i);
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
