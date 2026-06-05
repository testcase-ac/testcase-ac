#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readSpace();
    int l = inf.readInt(1, 20, "L");
    inf.readEoln();

    set<string> names;
    for (int i = 0; i < n; ++i) {
        string name = inf.readToken("[A-Z]{1,20}", "candidate");
        inf.readEoln();

        ensuref((int)name.size() == l,
                "candidate %d has length %d, expected %d",
                i + 1,
                (int)name.size(),
                l);
        ensuref(names.insert(name).second,
                "duplicate candidate at index %d: %s",
                i + 1,
                name.c_str());
    }

    inf.readEof();
}
