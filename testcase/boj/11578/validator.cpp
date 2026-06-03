#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        // CHECK: The statement names O_i as the count of solvable problems but
        // does not give explicit bounds; allow an empty list and cap by N.
        int oi = inf.readInt(0, n, "o_i");

        set<int> problems;
        for (int j = 1; j <= oi; ++j) {
            inf.readSpace();
            int p = inf.readInt(1, n, "p_ij");
            // CHECK: Problem numbers are described as the problems the student
            // can solve, so duplicates would make O_i inconsistent as a count.
            ensuref(problems.insert(p).second,
                    "duplicate problem number for student %d: %d", i, p);
        }
        inf.readEoln();
    }

    inf.readEof();
}
