#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "N");
    inf.readEoln();

    long long totalLength = 0;
    for (int i = 1; i <= n; ++i) {
        string s = inf.readToken("[a-z]{1,500000}", "s_i");
        inf.readEoln();
        totalLength += (long long)s.size();
        ensuref(totalLength <= 500000,
                "total length of names exceeds 500000 after s_%d: %lld", i,
                totalLength);
    }

    vector<bool> nonEmpty(n + 1, true);
    for (int op = 1; op <= n - 1; ++op) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readEoln();

        ensuref(i != j, "merge operation %d has equal indices: %d", op, i);
        ensuref(nonEmpty[i], "merge operation %d uses empty s_%d as target", op, i);
        ensuref(nonEmpty[j], "merge operation %d uses empty s_%d as source", op, j);

        nonEmpty[j] = false;
    }

    inf.readEof();
}
