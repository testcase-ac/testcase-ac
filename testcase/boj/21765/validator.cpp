#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readEoln();

    vector<int> seen_in_set(n + 1, 0);
    vector<bool> appears(n + 1, false);
    long long total_size = 0;

    for (int i = 1; i <= m; ++i) {
        setTestCase(i);

        // CHECK: The statement only says S_i is a subset of {1..N}, so empty sets are accepted.
        int size = inf.readInt(0, n, "size");
        total_size += size;
        ensuref(total_size <= 1000000LL,
                "sum of set sizes exceeds 1000000 after set %d", i);

        for (int j = 1; j <= size; ++j) {
            inf.readSpace();
            int person = inf.readInt(1, n, "person");
            ensuref(seen_in_set[person] != i,
                    "person %d appears more than once in set %d", person, i);
            seen_in_set[person] = i;
            appears[person] = true;
        }
        inf.readEoln();
    }

    for (int person = 1; person <= n; ++person) {
        ensuref(appears[person], "person %d does not appear in any set", person);
    }

    inf.readEof();
}
