#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "n");
    inf.readEoln();

    inf.readInts(n, 0, 100, "p_i");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int blownCoach = inf.readInt(1, n, "order_i");
        ensuref(!seen[blownCoach],
                "order_i is not a permutation: coach %d appears more than once",
                blownCoach);
        seen[blownCoach] = true;
    }
    inf.readEoln();

    inf.readEof();
}
