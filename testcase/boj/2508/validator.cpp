#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int tc = 0; tc < t; ++tc) {
        setTestCase(tc + 1);

        string separator = inf.readLine("[^]*", "separator");
        ensuref(separator.empty(),
                "expected blank separator before test case %d", tc + 1);

        int r = inf.readInt(1, 400, "r");
        inf.readSpace();
        int c = inf.readInt(1, 400, "c");
        inf.readEoln();

        vector<string> grid(r);
        for (int i = 0; i < r; ++i) {
            grid[i] = inf.readLine("[.o<>v^]{1,400}", "row");
            ensuref((int)grid[i].size() == c,
                    "Row %d length mismatch: expected %d, got %d",
                    i + 1, c, (int)grid[i].size());
        }
    }

    inf.readEof();
}
