#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 50, "m");
    inf.readEoln();

    set<string> seen;
    for (int i = 0; i < n; ++i) {
        string s = inf.readToken("[a-z]{1,50}", "s_i");
        inf.readEoln();

        ensuref((int)s.size() == m, "string %d has length %d, expected %d",
                i + 1, (int)s.size(), m);
        ensuref(seen.insert(s).second, "duplicate string at index %d: %s",
                i + 1, s.c_str());
    }

    inf.readEof();
}
