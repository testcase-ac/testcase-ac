#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int width = inf.readInt(136, 154, "width");
        inf.readSpace();
        int height = inf.readInt(68, 68, "height");
        inf.readEoln();

        ensuref(width == 136 || width == 142 || width == 148 || width == 154,
                "invalid bill width at index %d: %d", i + 1, width);
        ensuref(height == 68, "invalid bill height at index %d: %d", i + 1, height);
    }

    inf.readEof();
    return 0;
}
