#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int d = inf.readInt(1, 15, "D");
    inf.readSpace();
    int k = inf.readInt(1, d, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int count = inf.readInt(0, d, "d_i");
        set<int> seen;
        for (int j = 1; j <= count; ++j) {
            inf.readSpace();
            int problem = inf.readInt(1, d, "problem_i_j");
            ensuref(seen.insert(problem).second,
                    "student %d lists problem type %d more than once", i, problem);
        }
        inf.readEoln();
    }

    inf.readEof();
}
