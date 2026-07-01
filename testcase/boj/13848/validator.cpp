#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseIndex = 1;
    while (true) {
        int n = inf.readInt(0, 52, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        setTestCase(caseIndex++);

        vector<int> countByRank(14, 0);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }

            int rank = inf.readInt(1, 13, "c_i");
            ++countByRank[rank];
            ensuref(countByRank[rank] <= 4,
                    "rank %d appears %d times, more than four cards",
                    rank,
                    countByRank[rank]);
        }
        inf.readEoln();
    }

    inf.readEof();
}
