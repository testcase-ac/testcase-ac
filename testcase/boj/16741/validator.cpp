#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read r, s, p
    int r = inf.readInt(1, 500, "r");
    inf.readSpace();
    int s = inf.readInt(1, 500, "s");
    inf.readSpace();
    long long maxP = 2LL * r * s;
    int p = inf.readInt(1, maxP, "p");
    inf.readEoln();

    // Track used seats to ensure distinctness
    int cols = 2 * s; // seats per row
    vector<char> used((size_t)r * cols, 0);

    for (int k = 1; k <= p; k++) {
        string name_i = "i_" + to_string(k);
        int ik = inf.readInt(1, r, name_i);
        inf.readSpace();
        string name_j = "j_" + to_string(k);
        int jk = inf.readInt(1, cols, name_j);
        inf.readEoln();

        int idx = (ik - 1) * cols + (jk - 1);
        ensuref(!used[idx],
                "Duplicate seat at passenger %d: (%d, %d)",
                k, ik, jk);
        used[idx] = 1;
    }

    inf.readEof();
    return 0;
}
