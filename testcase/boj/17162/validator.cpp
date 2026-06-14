#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 200000, "Q");
    inf.readSpace();
    inf.readInt(1, 100, "mod");
    inf.readEoln();

    int type_three_count = 0;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 3, "query_type");

        if (type == 1) {
            inf.readSpace();
            inf.readInt(1, 2147483647, "num");
        } else if (type == 3) {
            ++type_three_count;
        }

        inf.readEoln();
    }

    ensuref(type_three_count >= 1, "there must be at least one type 3 query");
    inf.readEof();
}
