#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 2000;
    const int MAXM = 2000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int M = inf.readInt(1, MAXM, "M");
    inf.readEoln();

    vector<string> B(N);
    for (int i = 0; i < N; i++) {
        B[i] = inf.readToken("[UDLR]{1,2000}", "B_i");
        inf.readEoln();
        ensuref((int)B[i].size() == M,
                "Row %d of B has length %d, expected %d",
                i + 1, (int)B[i].size(), M);
    }

    const int COST_MIN = 1;
    const int COST_MAX = 500;

    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(M, COST_MIN, COST_MAX, "Cost_i");
        inf.readEoln();
        // No extra constraints on costs besides range and canonical form.
        (void)row;
    }

    inf.readEof();
}
