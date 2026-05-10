#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 2 * N, "M");
    inf.readEoln();

    // There are seats only on rows 1 and 3, columns 1..N.
    // Ensure no two staff occupy the same seat.
    vector<char> seen(2 * N, 0);
    for (int i = 0; i < M; i++) {
        int x = inf.readInt(1, 3, "x_i");
        ensuref(x == 1 || x == 3,
                "x_i must be 1 or 3, found %d at staff index %d", x, i);
        inf.readSpace();
        int y = inf.readInt(1, N, "y_i");
        inf.readSpace();
        int t = inf.readInt(0, 1, "t_i");
        inf.readEoln();

        int idx = (x == 1 ? 0 : N) + (y - 1);
        ensuref(!seen[idx],
                "Duplicate staff at seat (%d, %d) on staff index %d", x, y, i);
        seen[idx] = 1;
    }

    inf.readEof();
    return 0;
}
