#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int k = inf.readInt(1, 10000000, "k");
    inf.readEoln();

    vector<long long> totals(n, 0);
    bool reaches = false;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int a = inf.readInt(1, 10000000, "a_i_j");
            totals[i] += a;
            if (totals[i] >= k) {
                reaches = true;
            }
        }
        inf.readEoln();
    }

    ensuref(reaches, "no person reaches k");
    inf.readEof();
}
