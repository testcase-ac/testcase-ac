#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int groupCount = 0;
    while (true) {
        int n = inf.readInt(0, 20, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ensuref(n >= 5, "n must be at least 5, got %d", n);
        ++groupCount;
        // CHECK: The statement has no group count limit; this follows the local
        // default cap for unbounded multi-case inputs.
        ensuref(groupCount <= 100000,
                "number of groups exceeds 100000");
        setTestCase(groupCount);

        set<string> names;
        for (int i = 0; i < n; ++i) {
            string name = inf.readToken("[a-zA-Z]{1,60}", "name");
            // CHECK: The statement describes n named people; duplicate names
            // would make the reported speaker/listener identities ambiguous.
            ensuref(names.insert(name).second,
                    "duplicate name in group %d: %s",
                    groupCount,
                    name.c_str());

            for (int j = 0; j < n - 1; ++j) {
                inf.readSpace();
                inf.readToken("P|N", "message");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
