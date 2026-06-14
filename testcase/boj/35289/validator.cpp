#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long total = 0;
    for (int i = 0; i < 6; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int count = inf.readInt(0, 1000000, format("count_%d", i + 1));
        total += count;
    }
    inf.readEoln();
    ensuref(total >= 1, "at least one card must be present");
    inf.readEof();
}
