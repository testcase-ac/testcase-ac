#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    vector<int> count(n + 1, 0);
    for (int i = 1; i <= 2 * n; ++i) {
        int x = inf.readInt(1, n, "X_i");
        ++count[x];
        if (i < 2 * n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    for (int k = 1; k <= n; ++k) {
        ensuref(count[k] == 2, "value %d appears %d times, expected 2", k, count[k]);
    }

    inf.readEof();
    return 0;
}
