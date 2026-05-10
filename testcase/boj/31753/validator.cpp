#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Read the grid: exactly N lines, each of length M, only '.' or '#'
    for (int i = 0; i < N; ++i) {
        string row = inf.readLine("[.#]{1,50}", "row");
        ensuref((int)row.size() == M,
                "Row %d must have exactly %d characters, but has %d",
                i + 1, M, (int)row.size());
        for (int j = 0; j < M; ++j) {
            ensuref(row[j] == '.' || row[j] == '#',
                    "Invalid character '%c' at row %d, column %d (only '.' or '#' allowed)",
                    row[j], i + 1, j + 1);
        }
    }

    // No extra data
    inf.readEof();
}
