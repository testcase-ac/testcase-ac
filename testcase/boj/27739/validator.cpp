#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 2000, "N");
    inf.readSpace();
    int k = inf.readInt(2, n, "K");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }

        int value = inf.readInt(1, n, "A_i");
        ensuref(!seen[value], "A_%d repeats value %d", i, value);
        seen[value] = true;
    }
    inf.readEoln();
    inf.readEof();
}
