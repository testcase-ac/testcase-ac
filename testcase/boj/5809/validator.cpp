#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 100, "K");
    inf.readEoln();

    for (int tc = 1; tc <= k; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 600, "N");
        inf.readEoln();

        for (int row = 1; row <= n; ++row) {
            string cells = inf.readLine("[#.]{1,600}", "row");
            ensuref((int)cells.size() == n,
                    "row %d length must be N=%d, found %d",
                    row, n, (int)cells.size());
        }
    }

    inf.readEof();
}
