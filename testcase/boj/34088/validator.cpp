#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20000, "N");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int a = inf.readInt(1, 1000000000, "A_i");
        ensuref(seen.insert(a).second, "A_i values must be distinct, duplicate %d", a);
    }
    inf.readEoln();
    inf.readEof();
}
