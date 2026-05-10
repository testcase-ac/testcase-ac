#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 50, "N");
    inf.readEoln();

    // Store the input for global check
    vector<vector<int>> inning(N, vector<int>(9));

    for (int i = 0; i < N; ++i) {
        inning[i] = inf.readInts(9, 0, 4, "inning_results");
        inf.readEoln();

        // Check that at least one player has result 0 (out) in this inning
        bool has_out = false;
        for (int j = 0; j < 9; ++j) {
            if (inning[i][j] == 0) {
                has_out = true;
                break;
            }
        }
        ensuref(has_out, "In inning %d, there must be at least one out (0) among the 9 results.", i+1);
    }

    inf.readEof();
}
