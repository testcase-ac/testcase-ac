#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int N = inf.readInt(1, 8, "N");
    inf.readSpace();
    int M = inf.readInt(1, 8, "M");
    inf.readEoln();

    // Read grid and count CCTVs
    int cctv_count = 0;
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(M, 0, 6, "cell");
        inf.readEoln();
        for (int x : row) {
            if (1 <= x && x <= 5) {
                cctv_count++;
            }
        }
    }

    // Constraint: at most 8 CCTVs
    ensuref(cctv_count <= 8, "Number of CCTV (%d) exceeds maximum of 8", cctv_count);

    inf.readEof();
    return 0;
}
