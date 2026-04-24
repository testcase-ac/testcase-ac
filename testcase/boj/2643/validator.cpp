#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of rectangles
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Each rectangle: two side lengths, natural numbers < 1000.
    // All rectangles must have distinct sizes (unordered).
    set<pair<int,int>> seen;
    for (int i = 0; i < N; i++) {
        int a = inf.readInt(1, 999, "side_a");
        inf.readSpace();
        int b = inf.readInt(1, 999, "side_b");
        inf.readEoln();

        // Normalize the pair so that (min, max) is used for checking duplicates
        int x = min(a, b);
        int y = max(a, b);
        ensuref(!seen.count({x, y}),
                "Duplicate rectangle detected at index %d: sides (%d, %d)",
                i + 1, a, b);
        seen.insert({x, y});
    }

    inf.readEof();
    return 0;
}
