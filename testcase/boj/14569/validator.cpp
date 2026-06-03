#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int k = inf.readInt(4, 50, "k");
        vector<bool> seen(51, false);
        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            int t = inf.readInt(1, 50, "t_i");
            // CHECK: the statement gives k as the number of class periods,
            // so repeated period numbers would not describe k distinct periods.
            ensuref(!seen[t],
                    "duplicate class period %d in course %d", t, i + 1);
            seen[t] = true;
        }
        inf.readEoln();
    }

    int m = inf.readInt(1, 10000, "M");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int p = inf.readInt(0, 50, "p");
        vector<bool> seen(51, false);
        for (int j = 0; j < p; ++j) {
            inf.readSpace();
            int q = inf.readInt(1, 50, "q_i");
            // CHECK: p is described as the number of free periods, so repeated
            // period numbers would not describe p distinct free periods.
            ensuref(!seen[q],
                    "duplicate free period %d in student %d", q, i + 1);
            seen[q] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
