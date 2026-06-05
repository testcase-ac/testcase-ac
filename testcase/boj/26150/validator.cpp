#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    set<int> ids;
    for (int i = 1; i <= n; ++i) {
        string s = inf.readToken("[A-Za-z0-9]{1,100}", "s_i");
        inf.readSpace();
        int id = inf.readInt(1, 100000, "i_i");
        inf.readSpace();
        int d = inf.readInt(1, (int)s.size(), "d_i");
        inf.readEoln();

        ensuref(ids.insert(id).second, "duplicate problem number at row %d: %d", i, id);
        (void)d;
    }

    inf.readEof();
}
