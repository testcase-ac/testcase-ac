#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions and time
    int R = inf.readInt(1, 200, "R");
    inf.readSpace();
    int C = inf.readInt(1, 200, "C");
    inf.readSpace();
    long long N = inf.readLong(1LL, 1000000000LL, "N");
    inf.readEoln();

    // Read R lines of grid, each exactly C characters of '.' or 'O'
    for (int i = 0; i < R; i++) {
        string row = inf.readLine("[.O]+", "grid_row");
        ensuref((int)row.size() == C,
                "Row %d has length %d, expected %d", i+1, (int)row.size(), C);
        // Characters are guaranteed by regex to be only '.' or 'O'
    }

    inf.readEof();
    return 0;
}
