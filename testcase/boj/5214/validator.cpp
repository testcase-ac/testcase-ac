#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read M hyper-tube descriptions
    for (int i = 0; i < M; i++) {
        set<int> seen;
        for (int j = 0; j < K; j++) {
            int x = inf.readInt(1, N, "station");
            // Check for duplicate station in the same hyper-tube
            if (seen.count(x)) {
                ensuref(false, "Duplicate station %d in hyper-tube %d", x, i + 1);
            }
            seen.insert(x);
            if (j + 1 < K) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
