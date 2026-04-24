#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students N and number of friendships M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 1000, "M");
    inf.readEoln();

    // To detect duplicate edges (in either order) and self-loops
    set<pair<int,int>> seen;
    for (int i = 0; i < M; i++) {
        // Each friendship relation A B
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();

        int lineno = 2 + i; // First relation is on line 2
        // No self-loop allowed
        ensuref(A != B,
                "Self-loop detected at line %d: (%d, %d)", lineno, A, B);
        // No duplicate edge in the same direction
        ensuref(!seen.count({A, B}),
                "Duplicate edge detected at line %d: (%d, %d) repeated", lineno, A, B);
        // No duplicate edge in reverse direction
        ensuref(!seen.count({B, A}),
                "Duplicate edge detected at line %d: (%d, %d) repeats reverse of an earlier edge", lineno, A, B);

        // Record this edge (both directions for easy checking)
        seen.insert({A, B});
        seen.insert({B, A});
    }

    inf.readEof();
    return 0;
}
