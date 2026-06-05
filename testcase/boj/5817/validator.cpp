#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 200000, "M");
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int height = inf.readInt(1, n, "initial_height");
        ensuref(!seen[height], "initial arrangement repeats height %d", height);
        seen[height] = 1;
    }
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int type = inf.readInt(1, 2, "command_type");
        inf.readSpace();
        int first = inf.readInt(1, n, "command_first");
        inf.readSpace();
        int second = inf.readInt(1, n, "command_second");
        inf.readEoln();

        if (type == 1) {
            ensuref(first != second, "swap command %d has equal positions %d", i, first);
        } else {
            ensuref(first <= second, "query command %d has A=%d greater than B=%d", i, first, second);
        }
    }

    inf.readEof();
}
