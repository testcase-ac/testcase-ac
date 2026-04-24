#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of power plants (1 ≤ N ≤ 16)
    int N = inf.readInt(1, 16, "N");
    inf.readEoln();

    // Read cost matrix: N lines of N integers each, 0 ≤ cost ≤ 36
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(N, 0, 36, "cost");
        inf.readEoln();
    }

    // Read initial state string of length N, each character 'Y' or 'N'
    string state = inf.readToken("[YN]+", "state");
    inf.readEoln();
    ensuref((int)state.size() == N,
            "Length of state string (%d) does not match N (%d)",
            (int)state.size(), N);
    for (int i = 0; i < N; i++) {
        char c = state[i];
        ensuref(c == 'Y' || c == 'N',
                "Invalid character in state at position %d: '%c'", i, c);
    }

    // Read P: desired number of plants on (0 ≤ P ≤ N)
    int P = inf.readInt(0, N, "P");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
