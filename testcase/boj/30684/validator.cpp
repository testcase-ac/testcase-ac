#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<string> names;
    bool hasLengthThree = false;

    for (int i = 0; i < n; ++i) {
        string name = inf.readToken("[A-Z]{2,5}", "name_i");
        inf.readEoln();

        ensuref(names.insert(name).second, "duplicate name at index %d: %s", i + 1, name.c_str());
        hasLengthThree |= name.size() == 3;
    }

    ensuref(hasLengthThree, "at least one name must have length 3");

    inf.readEof();
}
