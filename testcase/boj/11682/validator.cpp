#include "testlib.h"
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readSpace();
    int A = inf.readInt(1, 100000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100000, "B");
    inf.readEoln();

    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readToken("[.#]{1,50}", "row");
        inf.readEoln();
        ensuref((int)grid[i].size() == M,
                "Row %d must have exactly %d characters, but has %d",
                i + 1, M, (int)grid[i].size());
    }

    // No additional global properties guaranteed by the statement
    // (e.g., connectivity, existence of answer) that must be validated.
    // The costs are always finite since we can always change heights.

    inf.readEof();
}
