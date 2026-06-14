#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    vector<char> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int value = inf.readInt(1, n, "P_i");
        ensuref(!seen[value], "duplicate permutation value at index %d: %d", i + 1, value);
        seen[value] = 1;
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}
