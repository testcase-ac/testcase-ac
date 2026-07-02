#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 4, "n");
    inf.readSpace();
    int w = inf.readInt(1, 10, "w");
    inf.readSpace();
    int h = inf.readInt(1, 10, "h");
    inf.readSpace();
    inf.readInt(1, 10, "l");
    inf.readEoln();

    vector<int> robot_count(n + 1, 0);
    int target_count = 0;

    for (int row_index = 1; row_index <= h; ++row_index) {
        string row = inf.readLine("[WX1234.]{1,10}", "row");
        ensuref(static_cast<int>(row.size()) == w,
                "row %d has length %d, expected %d", row_index,
                static_cast<int>(row.size()), w);

        for (int col_index = 1; col_index <= w; ++col_index) {
            char cell = row[col_index - 1];
            if (cell == 'X') {
                ++target_count;
            } else if ('1' <= cell && cell <= '4') {
                int robot = cell - '0';
                ensuref(robot <= n, "robot %d appears when n is %d at (%d, %d)",
                        robot, n, row_index, col_index);
                ++robot_count[robot];
            }
        }
    }

    ensuref(target_count == 1, "expected exactly one target cell, found %d",
            target_count);
    for (int robot = 1; robot <= n; ++robot) {
        ensuref(robot_count[robot] == 1,
                "expected exactly one robot %d, found %d", robot,
                robot_count[robot]);
    }

    inf.readEof();
}
