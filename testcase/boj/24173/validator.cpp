#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 500000, "n");
    inf.readSpace();
    inf.readInt(1, 100000000, "k");
    inf.readEoln();

    set<int> values;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int value = inf.readInt(1, 1000000000, "a_i");
        ensuref(values.insert(value).second, "duplicate A_%d value: %d", i + 1, value);
    }
    inf.readEoln();

    inf.readEof();
}
