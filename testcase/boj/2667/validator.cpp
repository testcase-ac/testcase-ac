#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the size of the map N
    int N = inf.readInt(5, 25, "N");
    inf.readEoln();

    // Read N lines, each must be exactly N characters of '0' or '1'
    for (int i = 0; i < N; i++) {
        // Read the row as a token (no spaces allowed)
        string row = inf.readToken("[01]+", "row");
        inf.readEoln();

        // Check its length
        ensuref((int)row.size() == N,
                "Row %d has length %d, expected %d",
                i + 1, (int)row.size(), N);

        // Check each character
        for (int j = 0; j < N; j++) {
            char c = row[j];
            ensuref(c == '0' || c == '1',
                    "Row %d, column %d: expected '0' or '1', found '%c'",
                    i + 1, j + 1, c);
        }
    }

    inf.readEof();
    return 0;
}
