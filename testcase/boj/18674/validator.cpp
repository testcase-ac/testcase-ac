#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const unsigned long long MAX_VALUE = 18446744073709551615ULL;

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int A = inf.readInt(0, 10000, "A");
        inf.readSpace();
        int B = inf.readInt(0, 10000, "B");
        inf.readEoln();

        int count = A + B + 1;
        for (int i = 1; i <= count; ++i) {
            inf.readUnsignedLong(0ULL, MAX_VALUE, "value");
            if (i < count) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
