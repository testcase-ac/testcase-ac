#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[0-9#]{1,100}", "row");
        ensuref((int)row.size() == n, "row %d has length %d, expected %d", i + 1,
                (int)row.size(), n);
        for (int j = 0; j < n; ++j) {
            bool border = i == 0 || i == n - 1 || j == 0 || j == n - 1;
            if (border) {
                ensuref('0' <= row[j] && row[j] <= '8',
                        "border cell (%d, %d) must be an opened digit, found '%c'",
                        i + 1, j + 1, row[j]);
            } else {
                ensuref(row[j] == '#',
                        "inner cell (%d, %d) must be closed '#', found '%c'",
                        i + 1, j + 1, row[j]);
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
