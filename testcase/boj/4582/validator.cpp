#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasetCount = 0;
    while (true) {
        int n = inf.readInt(0, 29999, "n");
        if (n == 0) {
            inf.readEoln();
            ensuref(datasetCount >= 1, "input must contain at least one dataset");
            inf.readEof();
            return 0;
        }

        inf.readSpace();
        int g = inf.readInt(1, 249, "g");
        inf.readEoln();

        ++datasetCount;
        ensuref(datasetCount <= 20, "too many datasets: %d", datasetCount);

        int totalQueens = 0;
        set<pair<int, int>> positions;
        for (int pattern = 1; pattern <= g; ++pattern) {
            int k = inf.readInt(1, n, "k");
            inf.readSpace();
            int x = inf.readInt(1, n, "x");
            inf.readSpace();
            int y = inf.readInt(1, n, "y");
            inf.readSpace();
            int s = inf.readInt(-29998, 29998, "s");
            inf.readSpace();
            int t = inf.readInt(-29998, 29998, "t");
            inf.readEoln();

            if (k == 1) {
                ensuref(s == 0 && t == 0,
                        "pattern %d has k = 1 but step is (%d, %d)", pattern, s, t);
            }

            totalQueens += k;
            ensuref(totalQueens <= n,
                    "dataset %d has too many queen positions: %d > %d",
                    datasetCount, totalQueens, n);

            for (int i = 0; i < k; ++i) {
                int px = x + i * s;
                int py = y + i * t;
                ensuref(1 <= px && px <= n && 1 <= py && py <= n,
                        "dataset %d pattern %d queen %d is off-board: (%d, %d)",
                        datasetCount, pattern, i + 1, px, py);
                ensuref(positions.insert({px, py}).second,
                        "dataset %d repeats queen position (%d, %d)",
                        datasetCount, px, py);
            }
        }
    }
}
