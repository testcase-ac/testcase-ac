#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    while (true) {
        int w = inf.readInt(0, 20, "w");
        inf.readSpace();
        int h = inf.readInt(0, 20, "h");
        inf.readEoln();

        if (w == 0 && h == 0) {
            break;
        }

        ensuref(w >= 1 && h >= 1, "non-terminal map size must satisfy 1 <= w,h <= 20");

        int robotCount = 0;
        int dirtyCount = 0;
        for (int y = 0; y < h; ++y) {
            string row = inf.readLine("[.*xo]{" + to_string(w) + "}", "row");
            for (char cell : row) {
                if (cell == 'o') {
                    ++robotCount;
                } else if (cell == '*') {
                    ++dirtyCount;
                }
            }
        }

        ensuref(robotCount == 1, "each map must contain exactly one robot, found %d", robotCount);
        ensuref(dirtyCount <= 10, "dirty tile count must not exceed 10, found %d", dirtyCount);
    }

    inf.readEof();
}
