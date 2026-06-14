#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[01X]{1,1000}", "row");
        ensuref((int)row.size() == n,
                "row %d has length %d, expected %d", i, (int)row.size(), n);

        for (int j = 0; j < n; ++j) {
            if (i == j) {
                ensuref(row[j] == 'X',
                        "diagonal entry (%d, %d) must be X", i, j);
            } else {
                ensuref(row[j] == '0' || row[j] == '1',
                        "off-diagonal entry (%d, %d) must be 0 or 1", i, j);
            }
        }
    }

    inf.readEof();
    return 0;
}
