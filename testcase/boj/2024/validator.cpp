#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 50000, "M");
    inf.readEoln();

    int segment_count = 0;
    while (true) {
        int l = inf.readInt(-50000, 50000, "L_i");
        inf.readSpace();
        int r = inf.readInt(-50000, 50000, "R_i");
        inf.readEoln();

        if (l == 0 && r == 0) {
            break;
        }

        ++segment_count;
        ensuref(segment_count <= 100000, "too many segments: %d", segment_count);
        ensuref(l <= r, "segment %d has L_i > R_i: %d > %d", segment_count, l, r);
    }

    inf.readEof();
}
