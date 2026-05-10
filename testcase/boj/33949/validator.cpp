#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read S and Q
    int S = inf.readInt(1, 200000, "S");
    inf.readSpace();
    int Q = inf.readInt(1, 500000, "Q");
    inf.readEoln();

    int count_type2 = 0;
    for (int i = 0; i < Q; ++i) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            inf.readSpace();
            int a = inf.readInt(1, S, "a");
            inf.readSpace();
            inf.readInt(-1000000000, 1000000000, "b");
            inf.readEoln();
        } else {
            count_type2++;
            inf.readEoln();
        }
    }

    ensuref(count_type2 >= 1, "At least one action of type 2 must be present in the input.");

    inf.readEof();
}
