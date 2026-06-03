#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 50, "n");
    inf.readSpace();
    int m = inf.readInt(1, 250, "m");
    inf.readEoln();

    int start_count = 0;
    int key_count = 0;
    for (int r = 0; r < n; ++r) {
        string row = inf.readToken("[01SK]{4,50}", "row");
        inf.readEoln();

        ensuref((int)row.size() == n, "row %d has length %d, expected %d", r + 1, (int)row.size(), n);
        for (int c = 0; c < n; ++c) {
            char cell = row[c];
            bool is_border = r == 0 || r == n - 1 || c == 0 || c == n - 1;
            ensuref(!is_border || cell == '1', "border cell (%d, %d) is '%c', expected wall", r + 1, c + 1, cell);

            if (cell == 'S') {
                ++start_count;
            } else if (cell == 'K') {
                ++key_count;
            }
        }
    }

    ensuref(start_count == 1, "expected exactly one S, found %d", start_count);
    ensuref(key_count == m, "expected exactly %d K cells, found %d", m, key_count);

    inf.readEof();
}
