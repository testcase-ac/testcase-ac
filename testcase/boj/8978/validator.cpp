#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    int k = inf.readInt(1, 10, "K");
    inf.readEoln();

    int p = inf.readInt(1, n * k, "P");
    inf.readEoln();

    set<string> names;
    for (int i = 0; i < p; ++i) {
        string name = inf.readToken("[a-z]{1,10}", "name");
        ensuref(names.insert(name).second, "duplicate passenger name: %s",
                name.c_str());
        inf.readEoln();
    }

    inf.readEof();
}
