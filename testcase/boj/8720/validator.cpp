#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int score = inf.readInt(0, 100, "score");
            ensuref(score == 0 || score == 100,
                    "score at participant %d task %d is %d, expected 0 or 100",
                    i + 1, j + 1, score);
            if (j + 1 < m) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
