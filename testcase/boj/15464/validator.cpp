#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    vector<int> seenPositions(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int a = inf.readInt(1, n, "a_i");
        ensuref(!seenPositions[a], "a_i is not distinct: position %d appears more than once", a);
        seenPositions[a] = 1;
    }
    inf.readEoln();

    set<int> ids;
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int id = inf.readInt(1000000, 9999999, "id_i");
        ensuref(ids.insert(id).second, "cow ID is not distinct: %d", id);
    }
    inf.readEoln();

    inf.readEof();
}
