#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(3, 500000, "Q");
    inf.readEoln();

    int length = 0;
    int type2Count = 0;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        if (type == 1) {
            inf.readSpace();
            inf.readInt(1, 1000, "x");
            ++length;
        } else {
            ensuref(length >= 2, "query %d has type 2 with current length %d", i, length);
            ++type2Count;
            length = (length + 1) / 2;
        }
        inf.readEoln();
    }

    ensuref(type2Count >= 1, "at least one type 2 query is required");
    inf.readEof();
}
