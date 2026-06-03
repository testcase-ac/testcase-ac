#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int a = inf.readInt(1, n, "a_i");
        ensuref(!seen[a], "duplicate sequence value at index %d: %d", i, a);
        seen[a] = 1;
    }
    inf.readEoln();
    inf.readEof();
}
