#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read scores and check constraints
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        // Each score is a positive integer < 20000
        a[i] = inf.readInt(1, 19999, "score");
        inf.readEoln();
        // Global property: since we need a strictly increasing positive sequence
        // achievable by only decreasing, we require a[i] >= i+1
        ensuref(a[i] >= i + 1,
                "For level %d, score = %d is too small; must be >= %d to allow a strictly increasing sequence",
                i + 1, a[i], i + 1);
    }

    inf.readEof();
    return 0;
}
