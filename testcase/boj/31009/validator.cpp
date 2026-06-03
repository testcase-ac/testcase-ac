#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    set<string> destinations;
    int jinjuCount = 0;
    for (int i = 0; i < n; ++i) {
        string destination = inf.readToken("[a-z]{1,15}", "D_i");
        inf.readSpace();
        inf.readInt(1, 1000, "C_i");
        inf.readEoln();

        ensuref(destinations.insert(destination).second,
                "duplicate destination at line %d: %s", i + 2,
                destination.c_str());
        if (destination == "jinju") {
            ++jinjuCount;
        }
    }

    ensuref(jinjuCount == 1, "expected exactly one jinju destination, found %d",
            jinjuCount);
    inf.readEof();
}
