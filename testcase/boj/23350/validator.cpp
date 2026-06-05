#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readEoln();

    vector<int> priorityCount(m + 1, 0);
    for (int i = 0; i < n; ++i) {
        int p = inf.readInt(1, m, "P");
        inf.readSpace();
        inf.readInt(1, 100, "W");
        inf.readEoln();

        ++priorityCount[p];
    }

    for (int p = 1; p <= m; ++p) {
        ensuref(priorityCount[p] > 0,
                "priority %d must appear at least once",
                p);
    }

    inf.readEof();
}
