#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readEoln();

    set<string> seen;
    for (int i = 0; i < n; ++i) {
        string value = inf.readToken("[1-9]{4}", "a_i");
        inf.readEoln();

        ensuref(seen.insert(value).second, "duplicate value at index %d: %s", i + 1, value.c_str());
    }

    inf.readEof();
}
