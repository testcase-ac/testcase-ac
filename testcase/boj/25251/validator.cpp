#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read h and w
    int h = inf.readInt(1, 2000, "h");
    inf.readSpace();
    int w = inf.readInt(1, 2000, "w");
    inf.readEoln();

    // Read h lines, each with w characters, only 'C' or '_'
    for (int i = 0; i < h; ++i) {
        string line = inf.readLine("[C_]{1,2000}", "grid_row");
        ensuref(int(line.size()) == w, "Line %d: Expected %d characters, got %d", i+1, w, int(line.size()));
    }

    inf.readEof();
}
