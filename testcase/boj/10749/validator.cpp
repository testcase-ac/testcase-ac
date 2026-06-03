#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    set<int> ids;
    for (int i = 0; i < n; ++i) {
        int id = inf.readInt(1, (1 << 30) - 1, "team_id");
        inf.readEoln();
        ensuref(ids.insert(id).second, "duplicate team ID at index %d: %d", i + 1, id);
    }

    inf.readEof();
}
