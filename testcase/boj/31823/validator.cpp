#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200, "M");
    inf.readEoln();

    set<string> names;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            inf.readToken("[*.]", "activity");
            inf.readSpace();
        }

        string name = inf.readToken("[a-z]{1,10}", "name");
        ensuref(names.insert(name).second, "duplicate name: %s", name.c_str());
        inf.readEoln();
    }

    inf.readEof();
}
