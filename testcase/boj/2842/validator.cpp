#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 50, "N");
    inf.readEoln();

    // Read the grid: N lines of length N, characters in {P, K, .}
    int pCount = 0;
    int kCount = 0;
    string rowRegex = "[PK\\.]{"+ to_string(N) +","+ to_string(N) +"}";
    for (int i = 0; i < N; i++) {
        string s = inf.readLine(rowRegex.c_str(), "grid_row");
        for (char c : s) {
            if (c == 'P') {
                pCount++;
            } else if (c == 'K') {
                kCount++;
            }
        }
    }
    // Must have exactly one post office and at least one house
    ensuref(pCount == 1, "There must be exactly one 'P' in the grid, found %d", pCount);
    ensuref(kCount >= 1, "There must be at least one 'K' in the grid, found %d", kCount);

    // Read the altitudes: N lines, each with N numbers in [1,1e6]
    for (int i = 0; i < N; i++) {
        inf.readLongs(N, 1LL, 1000000LL, "altitude");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
