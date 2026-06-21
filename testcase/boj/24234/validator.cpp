#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 10000, "Q");
    inf.readEoln();

    long long totalSize = 0;
    for (int i = 1; i <= n; ++i) {
        int s = inf.readInt(1, 1000000, "S");
        totalSize += s;
        ensuref(totalSize <= 1000000,
                "sum of sequence sizes exceeds 1000000 after sequence %d", i);

        for (int j = 1; j <= s; ++j) {
            inf.readSpace();
            inf.readInt(1, 10000, "A_i");
        }
        inf.readEoln();
    }

    set<int> queries;
    for (int i = 1; i <= q; ++i) {
        int query = inf.readInt(1, 10000, "Q_i");
        ensuref(queries.insert(query).second, "duplicate query value: %d", query);
        inf.readEoln();
    }

    inf.readEof();
}
