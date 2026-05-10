#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of tasks
    int N = inf.readInt(3, 10000, "N");
    inf.readEoln();

    // For each task i = 1..N, read its time, dependency count, and the list of dependencies
    for (int i = 1; i <= N; i++) {
        // Time for task i
        int t = inf.readInt(1, 100, "time");
        inf.readSpace();

        // Number of dependencies for task i
        int c = inf.readInt(0, 100, "cnt");
        // It is specified that dependencies of task i must be numbered from 1 to (i-1)
        ensuref(c <= i - 1,
                "Task %d has %d dependencies, but must have at most %d (since dependencies are < %d)",
                i, c, i - 1, i);

        if (c > 0) {
            // There must be a space before listing dependencies
            inf.readSpace();
            // Read exactly c integers, each in [1, i-1]
            vector<int> deps = inf.readInts(c, 1, i - 1, "dep");
            inf.readEoln();

            // Ensure there are no duplicate dependencies
            set<int> s(deps.begin(), deps.end());
            ensuref((int)s.size() == c,
                    "Task %d has duplicate dependency indices", i);
        } else {
            // If c == 0, the line should end directly after the zero
            inf.readEoln();
        }
    }

    // No extra content after this
    inf.readEof();
    return 0;
}
