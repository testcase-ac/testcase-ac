#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int instances = 0;
    int totalRelations = 0;

    while (true) {
        int n = inf.readInt(0, 26, "n");
        inf.readSpace();
        int m = inf.readInt(0, 100000, "m");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        ensuref(2 <= n && n <= 26, "n must be between 2 and 26 for a problem instance, got %d", n);
        ensuref(m >= 1, "m must be positive for a problem instance, got %d", m);
        // CHECK: The statement gives no upper bound for instance count or total relations.
        // Keep the accepted aggregate workload small enough for practical validation.
        ensuref(++instances <= 100000, "too many problem instances");
        totalRelations += m;
        ensuref(totalRelations <= 100000, "too many relations across all instances");

        char maxLetter = char('A' + n - 1);
        string pattern = string("[A-") + maxLetter + "]<[A-" + maxLetter + "]";

        for (int i = 0; i < m; ++i) {
            string relation = inf.readToken(pattern, "relation");
            inf.readEoln();
            // CHECK: The statement restricts letters to the first n uppercase letters but
            // does not forbid duplicate or self-relations; those are consistency cases.
            (void)relation;
        }
    }

    inf.readEof();
}
