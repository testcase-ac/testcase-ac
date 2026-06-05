#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int rank = inf.readInt(1, n, "rank");
        ensuref(!seen[rank], "duplicate midterm rank at final rank %d: %d", i, rank);
        seen[rank] = true;
    }
    inf.readEoln();

    inf.readEof();
}
