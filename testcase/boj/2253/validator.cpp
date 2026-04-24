#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(0, N - 2, "M");
    inf.readEoln();

    // Read the M small-stone indices
    set<int> seen;
    for (int i = 0; i < M; i++) {
        int x = inf.readInt(2, N - 1, "small_stone");
        inf.readEoln();
        ensuref(!seen.count(x),
                "Duplicate small stone index %d", x);
        seen.insert(x);
    }

    inf.readEof();
    return 0;
}
