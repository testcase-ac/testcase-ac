#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInts(4, 1, 100, "initial_ingredient");
    inf.readEoln();

    inf.readInts(4, 1, 10, "ingredient_per_cookie");
    inf.readEoln();

    int q = inf.readInt(1, 30, "Q");
    inf.readEoln();

    for (int index = 1; index <= q; ++index) {
        int type = inf.readInt(1, 5, "query_type");
        inf.readSpace();
        if (type == 1) {
            inf.readInt(1, 20, "cookie_count");
        } else {
            inf.readInt(1, 100, "ingredient_amount");
        }
        inf.readEoln();
    }

    inf.readEof();
}
