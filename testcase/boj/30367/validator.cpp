#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500, "n");
    inf.readSpace();
    int m = inf.readInt(2, 500, "m");
    inf.readEoln();

    int starts = 0;
    int exits = 0;
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[SE.#]{2,500}", "row");
        inf.readEoln();

        ensuref((int)row.size() == m,
                "row %d length is %d, expected %d", i + 1, (int)row.size(), m);

        for (int j = 0; j < m; ++j) {
            if (row[j] == 'S') {
                ++starts;
            } else if (row[j] == 'E') {
                ++exits;
            }
        }
    }

    ensuref(starts == 1, "expected exactly one S, found %d", starts);
    ensuref(exits == 1, "expected exactly one E, found %d", exits);

    inf.readEof();
    return 0;
}
