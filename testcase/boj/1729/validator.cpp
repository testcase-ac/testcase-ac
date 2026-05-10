#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are always 6 lines, each with 6 integers between 0 and 9 (inclusive)
    const int N = 6;
    for (int i = 0; i < N; ++i) {
        // Read 6 integers in [0,9]
        vector<int> row = inf.readInts(N, 0, 9, "a_ij");
        if (i < N - 1)
            inf.readEoln();
        else
            inf.readEoln(); // last line must also end with newline
    }

    inf.readEof();
}
