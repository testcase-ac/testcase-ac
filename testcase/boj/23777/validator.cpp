#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of sock groups
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // To ensure each (type, fit) pair appears at most once
    set<pair<string, string>> seen;

    for (int i = 0; i < n; i++) {
        // Read sock type: 1 to 20 lowercase letters
        string type = inf.readToken("[a-z]{1,20}", "type");
        inf.readSpace();

        // Read fit: exactly one of "left", "right", "any"
        string fit = inf.readToken("left|right|any", "fit");
        inf.readSpace();

        // Read count k: 1 to 1000
        int k = inf.readInt(1, 1000, "k");
        inf.readEoln();

        // Check uniqueness of (type, fit)
        auto pr = make_pair(type, fit);
        ensuref(seen.insert(pr).second,
                "Duplicate sock description for type \"%s\" with fit \"%s\"",
                type.c_str(), fit.c_str());
    }

    // No extra content
    inf.readEof();
    return 0;
}
