#include "testlib.h"
#include <vector>
#include <queue>
#include <string>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, K
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 1000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // 2. Read gym map
    vector<string> gym(N);
    for (int i = 0; i < N; ++i) {
        gym[i] = inf.readLine("[.#]{"+to_string(M)+","+to_string(M)+"}", "gym_row");
        ensuref((int)gym[i].size() == M, "Row %d length is %d, expected %d", i+1, (int)gym[i].size(), M);
    }

    // 3. Read x1, y1, x2, y2
    int x1 = inf.readInt(1, N, "x1");
    inf.readSpace();
    int y1 = inf.readInt(1, M, "y1");
    inf.readSpace();
    int x2 = inf.readInt(1, N, "x2");
    inf.readSpace();
    int y2 = inf.readInt(1, M, "y2");
    inf.readEoln();

    // 4. Check that (x1, y1) and (x2, y2) are different
    ensuref(!(x1 == x2 && y1 == y2), "Start and end positions must be different: (%d,%d)", x1, y1);

    // 5. Check that both positions are empty cells
    ensuref(gym[x1-1][y1-1] == '.', "Start position (%d,%d) is not an empty cell", x1, y1);
    ensuref(gym[x2-1][y2-1] == '.', "End position (%d,%d) is not an empty cell", x2, y2);

    // 6. Check that all characters are either '.' or '#'
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            ensuref(gym[i][j] == '.' || gym[i][j] == '#', "Invalid character '%c' at (%d,%d)", gym[i][j], i+1, j+1);
        }
    }

    // 7. Check that there is at least one path from (x1, y1) to (x2, y2)
    //    (Not required by statement: "If not possible, output -1", so do NOT check for connectivity.)

    // 8. No extra input
    inf.readEof();
}
