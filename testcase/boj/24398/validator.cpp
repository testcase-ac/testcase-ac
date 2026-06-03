#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10000, "N");
    inf.readSpace();
    int q = inf.readInt(1, n, "Q");
    inf.readSpace();
    inf.readInt(1, 100000000, "K");
    inf.readEoln();

    set<int> values;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int value = inf.readInt(1, 1000000000, "A_i");
        ensuref(values.insert(value).second, "A_i must be distinct, duplicate value %d at index %d", value, i + 1);
    }
    inf.readEoln();

    inf.readEof();
}
