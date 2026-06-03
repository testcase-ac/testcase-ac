#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 10, "k");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }

        int a = inf.readInt(1, n, "a_i");
        ensuref(!seen[a], "duplicate sequence value at index %d: %d", i, a);
        seen[a] = true;
    }
    inf.readEoln();

    inf.readEof();
}
