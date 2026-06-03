#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 54, "n");
    inf.readEoln();

    set<string> names;
    int count2026 = 0;
    for (int i = 0; i < n; ++i) {
        string name = inf.readToken("[a-z]{1,15}", "name");
        ensuref(names.insert(name).second, "duplicate department name at index %d: %s",
                i + 1, name.c_str());
        inf.readSpace();
        int year = inf.readInt(2001, 2026, "year");
        if (year == 2026) {
            ++count2026;
        }
        inf.readEoln();
    }

    ensuref(count2026 == 1, "expected exactly one department opened in 2026, found %d",
            count2026);
    inf.readEof();
}
