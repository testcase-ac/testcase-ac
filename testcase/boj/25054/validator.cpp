#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1500, "n");
    inf.readEoln();

    vector<bool> seen(n * n + 1, false);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) {
                inf.readSpace();
            }

            int age = inf.readInt(1, n * n, "a_i_j");
            ensuref(!seen[age], "duplicate age %d at row %d column %d", age, i, j);
            seen[age] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
}
