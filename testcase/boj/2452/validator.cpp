#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions M and N
    int M = inf.readInt(2, 100, "M");
    inf.readSpace();
    int N = inf.readInt(2, 100, "N");
    inf.readEoln();

    // Read the grid: M rows, each with N entries 0 or 1
    for (int i = 0; i < M; i++) {
        vector<int> row = inf.readInts(N, 0, 1, "grid");
        // Optionally, you could name each cell more precisely:
        // for (int j = 0; j < N; j++) {
        //     ensuref(row[j] == 0 || row[j] == 1,
        //             "Invalid value at row %d, column %d: %d (must be 0 or 1)",
        //             i+1, j+1, row[j]);
        // }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
