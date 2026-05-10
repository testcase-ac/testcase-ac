#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read N, M, K
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 10, "K");
    inf.readEoln();

    // Read the map: N rows, each with exactly M characters '0' or '1'
    for (int i = 0; i < N; i++) {
        // Build regex "[01]{M,M}"
        string len_spec = to_string(M) + "," + to_string(M);
        string regex = "[01]{" + len_spec + "}";
        string row = inf.readLine(regex.c_str(), "row");

        // Check the start and end cells are '0'
        if (i == 0) {
            ensuref(row[0] == '0',
                    "Start cell (1,1) must be '0', but found '%c'", row[0]);
        }
        if (i == N - 1) {
            ensuref(row[M-1] == '0',
                    "End cell (N,M) must be '0', but found '%c'", row[M-1]);
        }
    }

    inf.readEof();
    return 0;
}
