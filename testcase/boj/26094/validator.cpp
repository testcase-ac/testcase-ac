#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    vector<bool> used(n + 1, false);
    int schedulerSize = 0;

    for (int i = 1; i <= q; ++i) {
        int command = inf.readInt(0, 3, "command");

        if (command == 0) {
            inf.readSpace();
            int p = inf.readInt(1, n, "p");
            ensuref(!used[p], "job id %d is inserted more than once at command %d", p, i);
            used[p] = true;
            ++schedulerSize;
        } else if (command == 3) {
            ensuref(schedulerSize > 0, "pop command %d is issued on an empty scheduler", i);
            --schedulerSize;
        }

        inf.readEoln();
    }

    inf.readEof();
}
