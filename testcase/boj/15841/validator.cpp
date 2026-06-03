#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int queryCount = 0;
    while (true) {
        int hour = inf.readInt(-1, 490, "hour");
        inf.readEoln();

        if (hour == -1) {
            break;
        }

        ensuref(hour >= 1, "hour must be positive or -1 terminator: %d", hour);
        ++queryCount;
        // CHECK: statement does not bound the number of queried hours.
        ensuref(queryCount <= 100000, "too many queried hours: %d", queryCount);
    }

    inf.readEof();
}
