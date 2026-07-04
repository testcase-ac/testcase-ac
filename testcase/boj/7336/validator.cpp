#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Rectangle {
    int y1;
    int x1;
    int y2;
    int x2;
    int color;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCount = inf.readInt(1, 10, "M");
    inf.readEoln();

    for (int tc = 1; tc <= testCount; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 15, "N");
        inf.readEoln();

        vector<Rectangle> rectangles;
        rectangles.reserve(n);
        int boardHeight = 0;
        int boardWidth = 0;

        for (int i = 0; i < n; ++i) {
            int y1 = inf.readInt(0, 99, "upper_left_y");
            inf.readSpace();
            int x1 = inf.readInt(0, 99, "upper_left_x");
            inf.readSpace();
            int y2 = inf.readInt(0, 99, "lower_right_y");
            inf.readSpace();
            int x2 = inf.readInt(0, 99, "lower_right_x");
            inf.readSpace();
            int color = inf.readInt(1, 20, "color");
            inf.readEoln();

            ensuref(y1 < y2, "rectangle %d has non-positive height: y1=%d y2=%d", i + 1, y1, y2);
            ensuref(x1 < x2, "rectangle %d has non-positive width: x1=%d x2=%d", i + 1, x1, x2);

            rectangles.push_back({y1, x1, y2, x2, color});
            boardHeight = max(boardHeight, y2);
            boardWidth = max(boardWidth, x2);
        }

        ensuref(boardHeight > 0 && boardWidth > 0, "board must have positive dimensions");

        vector<vector<int>> covered(boardHeight, vector<int>(boardWidth, 0));
        for (int i = 0; i < n; ++i) {
            const Rectangle& rect = rectangles[i];
            for (int y = rect.y1; y < rect.y2; ++y) {
                for (int x = rect.x1; x < rect.x2; ++x) {
                    ++covered[y][x];
                    ensuref(covered[y][x] == 1,
                            "rectangles overlap at cell (%d, %d), including rectangle %d",
                            y, x, i + 1);
                }
            }
        }

        for (int y = 0; y < boardHeight; ++y) {
            for (int x = 0; x < boardWidth; ++x) {
                ensuref(covered[y][x] == 1, "board cell (%d, %d) is not covered", y, x);
            }
        }
    }

    inf.readEof();
}
