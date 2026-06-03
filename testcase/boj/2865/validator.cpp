#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    for (int genre = 1; genre <= m; ++genre) {
        vector<bool> seen(n + 1, false);
        double previousScore = 11.0;

        for (int pos = 1; pos <= n; ++pos) {
            int student = inf.readInt(1, n, "student");
            inf.readSpace();
            double score = inf.readDouble(0.0, 10.0, "score");

            ensuref(!seen[student],
                    "student %d appears more than once in genre %d", student, genre);
            seen[student] = true;

            // CHECK: Descending order is interpreted as non-increasing, so tied scores are valid.
            ensuref(score <= previousScore,
                    "scores are not in non-increasing order in genre %d at position %d: %.17g after %.17g",
                    genre, pos, score, previousScore);
            previousScore = score;

            if (pos < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
