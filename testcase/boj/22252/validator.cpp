#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    long long total_k = 0;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();
        inf.readToken("[a-zA-Z]{1,15}", "Name");
        inf.readSpace();

        if (type == 1) {
            int k = inf.readInt(1, 100000, "k");
            total_k += k;
            ensuref(total_k <= 1000000, "sum of k exceeds 1000000 at query %d", i);

            for (int j = 1; j <= k; ++j) {
                inf.readSpace();
                inf.readInt(1, 100000, "C_i");
            }
            inf.readEoln();
        } else {
            inf.readInt(1, 100000, "b");
            inf.readEoln();
        }
    }

    inf.readEof();
}
