#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no numeric bounds; cap aggregate maze cells to keep string input practical.
    const long long maxTotalCells = 1000000;
    long long totalCells = 0;

    // CHECK: The statement gives no bound for the number of data sets.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int dataset = 1; dataset <= n; ++dataset) {
        setTestCase(dataset);

        // CHECK: Dimensions are positive and otherwise unbounded in the statement.
        int f = inf.readInt(1, 1000, "f");
        inf.readSpace();
        int r = inf.readInt(1, 1000, "r");
        inf.readSpace();
        int c = inf.readInt(1, 1000, "c");
        inf.readEoln();

        long long cells = 1LL * f * r * c;
        totalCells += cells;
        ensuref(totalCells <= maxTotalCells,
                "total maze cells exceed cap: %lld > %lld", totalCells, maxTotalCells);

        int starts = 0;
        int exits = 0;
        string rowPattern = "[#\\.SE]{" + to_string(c) + "}";
        for (int layer = 1; layer <= f; ++layer) {
            for (int row = 1; row <= r; ++row) {
                string line = inf.readLine(rowPattern, "maze_row");
                for (char ch : line) {
                    starts += ch == 'S';
                    exits += ch == 'E';
                }
            }
        }

        ensuref(starts == 1, "dataset must contain exactly one start, found %d", starts);
        ensuref(exits == 1, "dataset must contain exactly one exit, found %d", exits);
    }

    inf.readEof();
}
