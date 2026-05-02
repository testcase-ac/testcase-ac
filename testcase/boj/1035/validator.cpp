#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int H = 5;
    const int W = 5;

    int starCount = 0;

    for (int i = 0; i < H; i++) {
        string row = inf.readLine("[.*]{5}", "row");
        ensuref((int)row.size() == W, "Row %d must have exactly %d characters", i + 1, W);

        for (char c : row) {
            if (c == '*') starCount++;
            else {
                ensuref(c == '.', "Invalid character '%c' in board. Only '.' and '*' allowed.", c);
            }
        }
    }

    ensuref(1 <= starCount && starCount <= 5,
            "Number of pieces '*' must be between 1 and 5, found %d", starCount);

    inf.readEof();
}
