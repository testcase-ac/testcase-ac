#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 50, "t");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read number of phone numbers in this test case
        int n = inf.readInt(1, 10000, "n");
        inf.readEoln();

        // Read each phone number, ensure it's digits only, length 1..10, and no duplicates
        set<string> seen;
        for (int i = 1; i <= n; i++) {
            string phone = inf.readToken("[0-9]{1,10}", "phone");
            inf.readEoln();
            bool inserted = seen.insert(phone).second;
            ensuref(inserted,
                    "Duplicate phone number in test case %d at index %d: %s",
                    tc, i, phone.c_str());
        }
    }

    inf.readEof();
    return 0;
}
