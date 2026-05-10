#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Mark current test case for better error reporting
        setTestCase(tc + 1);

        // Number of clothes
        int n = inf.readInt(0, 30, "n");
        inf.readEoln();

        // Each clothing item: name and type
        set<string> names;
        for (int i = 0; i < n; i++) {
            string name = inf.readToken("[a-z]{1,20}", "name");
            inf.readSpace();
            string type = inf.readToken("[a-z]{1,20}", "type");
            inf.readEoln();

            // Names must be unique within a test case
            ensuref(!names.count(name),
                    "Duplicate clothing name in test case %d at line %d: '%s'",
                    tc+1, 2 + tc*(n+1) + i, name.c_str());
            names.insert(name);
        }
    }

    // No extra content
    inf.readEof();
    return 0;
}
