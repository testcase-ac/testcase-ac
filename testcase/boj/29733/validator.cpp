#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 100, "R");
    inf.readSpace();
    int c = inf.readInt(1, 100, "C");
    inf.readSpace();
    int h = inf.readInt(1, 100, "H");
    inf.readEoln();

    for (int z = 0; z < h; ++z) {
        for (int y = 0; y < r; ++y) {
            string row = inf.readLine("[*.]{1,100}", "row");
            ensuref((int)row.size() == c,
                    "row length must be C at layer %d row %d: expected %d, got %d",
                    z + 1,
                    y + 1,
                    c,
                    (int)row.size());
        }
    }

    inf.readEof();
}
