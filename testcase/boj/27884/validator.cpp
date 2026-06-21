#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    set<string> names;
    for (int i = 0; i < n; ++i) {
        string name = inf.readToken("[A-Za-z0-9]{1,10}", "station_name");
        inf.readEoln();

        ensuref(names.insert(name).second,
                "duplicate station name at index %d: %s", i + 1, name.c_str());
    }

    inf.readEof();
}
