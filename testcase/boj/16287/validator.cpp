#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(10, 799994, "w");
    inf.readSpace();
    int n = inf.readInt(4, 5000, "n");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int a = inf.readInt(1, 200000, "a_i");
        ensuref(seen.insert(a).second, "duplicate A element at index %d: %d", i + 1, a);
    }
    inf.readEoln();

    inf.readEof();
}
