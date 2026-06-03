#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "m");
    inf.readEoln();

    vector<int> childCount(n + 1, 0);
    int rootParent = inf.readInt(-1, -1, "parent_1");
    (void)rootParent;
    for (int i = 2; i <= n; ++i) {
        inf.readSpace();
        int parent = inf.readInt(1, i - 1, "parent_i");
        ++childCount[parent];
    }
    inf.readEoln();

    for (int q = 1; q <= m; ++q) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();
        int employee = inf.readInt(1, n, "employee");

        if (type == 1) {
            inf.readSpace();
            int weight = inf.readInt(1, 1000, "w");
            (void)weight;
            ensuref(childCount[employee] > 0,
                    "type 1 query employee must have at least one direct subordinate: query %d employee %d",
                    q, employee);
        }

        inf.readEoln();
    }

    inf.readEof();
}
