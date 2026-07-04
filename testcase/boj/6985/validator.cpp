#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound the number of test cases. This keeps
    // validation finite while staying well above realistic tiny-grid inputs.
    int testCount = inf.readInt(1, 100000, "N");
    inf.readEoln();

    int totalObstacleRectangles = 0;
    for (int tc = 1; tc <= testCount; ++tc) {
        setTestCase(tc);

        int width = inf.readInt(1, 16, "X");
        inf.readSpace();
        int height = inf.readInt(1, 16, "Y");
        inf.readEoln();

        int startX = inf.readInt(0, width - 1, "x1_start");
        inf.readSpace();
        int startY = inf.readInt(0, height - 1, "y1_start");
        inf.readSpace();
        int finishX = inf.readInt(0, width - 1, "x2_finish");
        inf.readSpace();
        int finishY = inf.readInt(0, height - 1, "y2_finish");
        inf.readEoln();

        // CHECK: P has no written upper bound. A 16x16 grid can be described
        // cell-by-cell with 256 rectangles; this cap still permits many
        // redundant or overlapping obstacle rectangles.
        int obstacleCount = inf.readInt(0, 100000, "P");
        inf.readEoln();

        totalObstacleRectangles += obstacleCount;
        ensuref(totalObstacleRectangles <= 100000,
                "too many obstacle rectangles in aggregate: %d",
                totalObstacleRectangles);

        vector<vector<bool>> occupied(width, vector<bool>(height, false));
        for (int i = 1; i <= obstacleCount; ++i) {
            int left = inf.readInt(0, width - 1, "x1_obstacle");
            inf.readSpace();
            int right = inf.readInt(left, width - 1, "x2_obstacle");
            inf.readSpace();
            int bottom = inf.readInt(0, height - 1, "y1_obstacle");
            inf.readSpace();
            int top = inf.readInt(bottom, height - 1, "y2_obstacle");
            inf.readEoln();

            for (int x = left; x <= right; ++x) {
                for (int y = bottom; y <= top; ++y) {
                    occupied[x][y] = true;
                }
            }
        }

        ensuref(!occupied[startX][startY],
                "start point is occupied in test case %d", tc);
        ensuref(!occupied[finishX][finishY],
                "finish point is occupied in test case %d", tc);
    }

    inf.readEof();
}
