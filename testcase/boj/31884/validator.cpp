#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 150000, "Q");
    inf.readEoln();

    bool has_query_type_3 = false;
    for (int query_index = 1; query_index <= q; ++query_index) {
        int type = inf.readInt(1, 3, "type");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "i");
        inf.readEoln();

        if (type == 3) {
            has_query_type_3 = true;
        }
    }

    ensuref(has_query_type_3, "at least one type 3 query is required");
    inf.readEof();
}
