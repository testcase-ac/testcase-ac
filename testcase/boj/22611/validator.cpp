#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalCommands = 0;
    int dataset = 0;

    while (true) {
        int n = inf.readInt(0, 10000, "N");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++dataset;
        setTestCase(dataset);
        totalCommands += n;
        // CHECK: The statement gives no total dataset bound; cap aggregate work at one
        // largest dataset to keep generated validator inputs practical.
        ensuref(totalCommands <= 10000,
                "total command count exceeds practical cap: %lld", totalCommands);

        set<long long> writtenIds;
        for (int i = 1; i <= n; ++i) {
            string command = inf.readToken("[WDR]", "command");

            if (command == "W") {
                inf.readSpace();
                long long id = inf.readLong(0LL, 1000000000LL, "I");
                inf.readSpace();
                inf.readLong(1LL, 1000000000LL, "S");
                inf.readEoln();

                ensuref(writtenIds.insert(id).second,
                        "file id written more than once in dataset %d at command %d: %lld",
                        dataset, i, id);
            } else if (command == "D") {
                inf.readSpace();
                inf.readLong(0LL, 1000000000LL, "I");
                inf.readEoln();
            } else {
                inf.readSpace();
                inf.readLong(0LL, 1000000000LL, "P");
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
