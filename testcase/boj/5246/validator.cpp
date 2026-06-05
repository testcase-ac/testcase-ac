#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no board-count bound; use the local default cap.
    int boards = inf.readInt(1, 100000, "boards");
    inf.readEoln();

    for (int tc = 1; tc <= boards; ++tc) {
        setTestCase(tc);

        // CHECK: Empty boards are accepted because the maximum pieces on a row is well-defined as 0.
        int pieces = inf.readInt(0, 64, "pieces");

        set<pair<int, int>> occupied;
        for (int i = 1; i <= pieces; ++i) {
            inf.readSpace();
            int column = inf.readInt(1, 8, "column");
            inf.readSpace();
            int row = inf.readInt(1, 8, "row");
            // CHECK: A checkerboard position can contain at most one piece.
            ensuref(occupied.emplace(column, row).second,
                    "duplicate piece position in board %d: (%d, %d)", tc, column, row);
        }

        inf.readEoln();
    }

    inf.readEof();
}
