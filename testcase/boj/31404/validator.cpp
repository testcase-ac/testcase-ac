#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 64, "H");
    inf.readSpace();
    int w = inf.readInt(1, 64, "W");
    inf.readEoln();

    inf.readInt(0, h - 1, "R");
    inf.readSpace();
    inf.readInt(0, w - 1, "C");
    inf.readSpace();
    inf.readInt(0, 3, "D");
    inf.readEoln();

    for (int table = 0; table < 2; ++table) {
        for (int r = 0; r < h; ++r) {
            string row = inf.readLine("[0-3]{1,64}", table == 0 ? "A_row" : "B_row");
            ensuref((int)row.size() == w,
                    "%c row %d has length %d, expected %d",
                    table == 0 ? 'A' : 'B',
                    r,
                    (int)row.size(),
                    w);
        }
    }

    inf.readEof();
}
