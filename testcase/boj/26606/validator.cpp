#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even: %d", n);

    vector<bool> seen(101, false);
    for (int i = 1; i <= n / 2; ++i) {
        int a = inf.readInt(1, 100, "A_i_1");
        inf.readSpace();
        int b = inf.readInt(1, 100, "A_i_2");
        inf.readEoln();

        ensuref(!seen[a], "duplicate card value at row %d: %d", i, a);
        seen[a] = true;
        ensuref(!seen[b], "duplicate card value at row %d: %d", i, b);
        seen[b] = true;
    }

    inf.readEof();
    return 0;
}
