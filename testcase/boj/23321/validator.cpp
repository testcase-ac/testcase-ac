#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string rows[5];
    for (int i = 0; i < 5; ++i) {
        rows[i] = inf.readLine("[.owmlnL]{1,10000}", format("row_%d", i + 1));
    }

    int width = (int)rows[0].size();
    for (int i = 1; i < 5; ++i) {
        ensuref((int)rows[i].size() == width,
                "row %d has length %d, expected %d",
                i + 1,
                (int)rows[i].size(),
                width);
    }

    const string preparing = ".omln";
    const string jumping = "owln.";
    const string seated = "..oLn";

    for (int col = 0; col < width; ++col) {
        string pose;
        for (int row = 0; row < 5; ++row) {
            pose += rows[row][col];
        }
        ensuref(pose == preparing || pose == jumping || pose == seated,
                "column %d is not a valid student pose: %s",
                col + 1,
                pose.c_str());
    }

    inf.readEof();
}
