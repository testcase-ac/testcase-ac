#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 1000, "N");
    inf.readEoln();

    vector<int> required(6);
    for (int difficulty = 1; difficulty <= 5; ++difficulty) {
        required[difficulty] = inf.readInt(1, n - 1, "p_i");
        if (difficulty < 5) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    vector<int> countByDifficulty(6, 0);
    for (int i = 1; i <= n; ++i) {
        int k = inf.readInt(1, 5, "k_i");
        inf.readSpace();
        inf.readInt(1, 300, "t_i");
        inf.readEoln();
        ++countByDifficulty[k];
    }

    for (int difficulty = 1; difficulty <= 5; ++difficulty) {
        ensuref(countByDifficulty[difficulty] >= required[difficulty],
                "difficulty %d has %d problems, fewer than required %d",
                difficulty, countByDifficulty[difficulty],
                required[difficulty]);
    }

    inf.readEof();
    return 0;
}
