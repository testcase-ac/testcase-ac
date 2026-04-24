#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // We expect N unique integers in [-1e6, 1e6], each on its own line
    const int OFFSET = 1000000;
    const int RANGE = 2 * OFFSET + 1;
    vector<char> seen(RANGE, 0);

    for (int i = 0; i < N; i++) {
        int x = inf.readInt(-OFFSET, OFFSET, "a_i");
        inf.readEoln();

        int idx = x + OFFSET;
        ensuref(seen[idx] == 0,
                "Duplicate number %d found at line %d", x, i + 2);
        seen[idx] = 1;
    }

    // No extra content
    inf.readEof();
    return 0;
}
