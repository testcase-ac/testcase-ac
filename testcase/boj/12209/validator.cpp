#include "testlib.h"

#include <string>

using namespace std;

bool isValidTile(int value) {
    if (value == 0) {
        return true;
    }
    return value >= 2 && value <= 1024 && (value & (value - 1)) == 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 20, "N");
        inf.readSpace();
        string dir = inf.readToken("left|right|up|down", "DIR");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                int value = inf.readInt(0, 1024, "grid_value");
                ensuref(isValidTile(value),
                        "grid value at row %d column %d is not 0 or a power of two from 2 to 1024: %d",
                        i + 1, j + 1, value);
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
