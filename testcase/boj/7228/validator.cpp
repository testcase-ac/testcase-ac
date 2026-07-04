#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    set<pair<int, int>> seen;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int statementType = inf.readInt(0, 1, "m_i");
        inf.readEoln();

        ensuref(a != b, "self statement at index %d: (%d, %d)", i, a, b);
        ensuref(seen.emplace(a, b).second,
                "duplicate ordered pair at index %d: (%d, %d)", i, a, b);
        (void)statementType;
    }

    inf.readEof();
}
