#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    int m = inf.readInt(1, 50, "m");
    inf.readEoln();

    int start_count = 0;
    int delivery_count = 0;
    string row_pattern = "[SC#.]{%d}";

    for (int i = 0; i < n; ++i) {
        string row = inf.readLine(format(row_pattern.c_str(), m), "row");
        for (char cell : row) {
            if (cell == 'S') {
                ++start_count;
            } else if (cell == 'C') {
                ++delivery_count;
            }
        }
    }

    ensuref(start_count == 1, "expected exactly one S, found %d", start_count);
    ensuref(delivery_count == 2, "expected exactly two C cells, found %d", delivery_count);

    inf.readEof();
}
