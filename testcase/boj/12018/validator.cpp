#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    for (int subj = 0; subj < n; ++subj) {
        // Read P_i and L_i
        int P_i = inf.readInt(1, 100, "P_i");
        inf.readSpace();
        int L_i = inf.readInt(1, 100, "L_i");
        inf.readEoln();

        // Read P_i integers: the mileages
        vector<int> mileages = inf.readInts(P_i, 1, 36, "mileages");
        inf.readEoln();

        // No further per-subject constraints in the statement
    }

    inf.readEof();
}
