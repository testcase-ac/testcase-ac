#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 30000, "n");
        vector<bool> seen(n + 1, false);

        for (int i = 0; i < n; ++i) {
            inf.readSpace();
            int value = inf.readInt(1, n, "Fred_i");
            ensuref(!seen[value], "duplicate value in Fred at index %d: %d", i, value);
            seen[value] = true;
        }

        inf.readEoln();
    }

    inf.readEof();
}
