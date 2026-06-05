#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    set<int> sizes;
    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(1, 1000000000, "A_i");
        inf.readEoln();

        ensuref(sizes.insert(a).second,
                "duplicate cake piece size at index %d: %d", i + 1, a);
    }

    inf.readEof();
    return 0;
}
