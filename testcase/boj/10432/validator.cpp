#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 1000, "P");
    inf.readEoln();

    for (int tc = 1; tc <= p; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 1000000000, "K");

        for (int i = 0; i < 12; ++i) {
            inf.readSpace();
            // CHECK: The statement only says non-negative integer; cap at 1e9 to keep values practical.
            int value = inf.readInt(0, 1000000000, "a_i");
            if (i == 0 || i == 11) {
                ensuref(value == 0, "a_%d must be 0, got %d", i + 1, value);
            }
        }

        inf.readEoln();
    }

    inf.readEof();
}
