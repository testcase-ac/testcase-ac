#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 100, "N");
    inf.readEoln();

    // Read M
    int M = inf.readInt(3, 100, "M");
    inf.readEoln();

    // Read targets A[1..M]
    vector<int> A = inf.readInts(M, 1, N, "A");
    inf.readEoln();

    // Read each game's guesses B[i][1..N]
    for (int i = 1; i <= M; i++) {
        string name = "B_" + to_string(i);
        vector<int> B = inf.readInts(N, 1, N, name.c_str());
        inf.readEoln();

        int target = A[i - 1];
        // Validate that the target guesses themselves
        ensuref(B[target - 1] == target,
                "In game %d, B[%d][%d] = %d but should be %d (target must guess themselves)",
                i, i, target, B[target - 1], target);
    }

    inf.readEof();
    return 0;
}
