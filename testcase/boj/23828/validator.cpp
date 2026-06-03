#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 100000, "A_i");
    inf.readEoln();

    set<int> distinct(a.begin(), a.end());
    ensuref(m <= (int)distinct.size(),
            "M=%d exceeds the number of distinct A_i values: %d",
            m,
            (int)distinct.size());

    inf.readEof();
    return 0;
}
