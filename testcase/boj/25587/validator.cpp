#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, 1000, "a_i");
    inf.readEoln();
    vector<int> b = inf.readInts(n, 0, 1000, "b_i");
    inf.readEoln();

    bool has_type_two = false;
    for (int i = 1; i <= m; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        if (type == 1) {
            inf.readSpace();
            inf.readInt(1, n, "x");
            inf.readSpace();
            inf.readInt(1, n, "y");
        } else {
            has_type_two = true;
        }
        inf.readEoln();
    }

    ensuref(has_type_two, "at least one type-2 query is required");
    inf.readEof();
}
