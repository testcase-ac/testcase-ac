#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R, C, N
    int R = inf.readInt(1, 200, "R");
    inf.readSpace();
    int C = inf.readInt(1, 200, "C");
    inf.readSpace();
    int N = inf.readInt(1, 200, "N");
    inf.readEoln();

    // Read the grid: R lines, each exactly C characters of '.' or 'O'
    string row_regex = string("[.O]{") + to_string(C) + "," + to_string(C) + "}";
    for (int i = 0; i < R; i++) {
        inf.readLine(row_regex, "grid_row");
    }

    inf.readEof();
    return 0;
}
