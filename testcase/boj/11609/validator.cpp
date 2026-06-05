#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    set<pair<string, string>> seen;
    for (int i = 0; i < n; ++i) {
        string first = inf.readToken("[A-Z][a-z]{1,9}", "first");
        inf.readSpace();
        string last = inf.readToken("[A-Z][a-z]{1,9}", "last");
        inf.readEoln();

        ensuref(seen.insert({first, last}).second,
                "duplicate full name at index %d: %s %s",
                i + 1,
                first.c_str(),
                last.c_str());
    }

    inf.readEof();
}
