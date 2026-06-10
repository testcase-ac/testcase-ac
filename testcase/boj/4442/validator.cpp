#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxTotalN = 700000;
    int totalN = 0;
    int caseIndex = 1;

    while (true) {
        int n = inf.readInt(0, 100000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        setTestCase(caseIndex++);

        // CHECK: the statement gives no test-case count limit; cap total names
        // so validated inputs stay below the local practical string-size limit.
        ensuref(totalN <= maxTotalN - n, "total N exceeds %d", maxTotalN);
        totalN += n;

        set<string> frodo;
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            string name = inf.readToken("[A-Za-z]{1,6}", "frodo_name");
            ensuref(frodo.insert(name).second, "duplicate Frodo name: %s", name.c_str());
        }
        inf.readEoln();

        set<string> sam;
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            string name = inf.readToken("[A-Za-z]{1,6}", "sam_name");
            ensuref(sam.insert(name).second, "duplicate Sam name: %s", name.c_str());
            ensuref(frodo.count(name) == 1, "Sam name not in Frodo chart: %s", name.c_str());
        }
        inf.readEoln();

        ensuref(sam.size() == frodo.size(), "Sam chart name set differs from Frodo chart");
    }

    inf.readEof();
}
