#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int tc = 1; tc <= 3; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 10, "n");
        inf.readSpace();
        int m = inf.readInt(1, 10, "m");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            string row = inf.readToken("[.#]{1,10}", "row");
            ensuref((int)row.size() == m,
                    "row %d length is %d, expected %d", i + 1,
                    (int)row.size(), m);
            inf.readEoln();
        }
    }

    inf.readEof();
}
