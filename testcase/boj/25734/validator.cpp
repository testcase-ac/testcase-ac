#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    set<int> values;
    for (int i = 1; i <= q; ++i) {
        int op = inf.readInt(1, 2, "op");
        inf.readSpace();
        int x = inf.readInt(1, 1000000000, "x");
        inf.readEoln();

        if (op == 1) {
            ensuref(values.insert(x).second,
                    "operation %d inserts existing value %d", i, x);
        } else {
            auto it = values.find(x);
            ensuref(it != values.end(),
                    "operation %d deletes absent value %d", i, x);
            values.erase(it);
        }
    }

    inf.readEof();
}
