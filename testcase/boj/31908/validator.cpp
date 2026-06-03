#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    set<string> names;
    for (int i = 0; i < n; ++i) {
        string name = inf.readToken("[A-Za-z0-9_]{1,50}", "p_i");
        ensuref(names.insert(name).second, "duplicate name at row %d: %s", i + 1, name.c_str());

        inf.readSpace();

        string ring = inf.readToken("-|[A-Za-z0-9_]{1,50}", "s_i");
        inf.readEoln();
    }

    inf.readEof();
}
