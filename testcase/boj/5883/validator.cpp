#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    set<int> distinct;
    for (int i = 0; i < n; ++i) {
        int b = inf.readInt(0, 1000000, "B_i");
        inf.readEoln();
        distinct.insert(b);
    }

    ensuref(distinct.size() >= 2,
            "there must be at least two distinct B_i values, found %d",
            int(distinct.size()));

    inf.readEof();
    return 0;
}
