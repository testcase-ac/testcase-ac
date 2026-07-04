#include "testlib.h"

#include <string>

using namespace std;

namespace {

bool isSixDecimalProbability(const string& token) {
    if (token.size() != 8) return false;
    if (token[1] != '.') return false;
    if (token[0] < '0' || token[0] > '1') return false;
    for (int i = 2; i < 8; ++i) {
        if (token[i] < '0' || token[i] > '9') return false;
    }
    if (token[0] == '1') {
        for (int i = 2; i < 8; ++i) {
            if (token[i] != '0') return false;
        }
    }
    return true;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement does not bound t; cap total n to keep validation practical.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readEoln();

        int n = inf.readInt(1, 60, "n");
        inf.readEoln();
        totalN += n;
        ensuref(totalN <= 100000, "sum of n exceeds practical cap: %d", totalN);

        for (int i = 0; i < n; ++i) {
            string p = inf.readToken("[0-9].[0-9]{6}", "p_i");
            ensuref(isSixDecimalProbability(p),
                    "p_%d must be a probability with exactly 6 decimal places: %s",
                    i + 1, p.c_str());
            if (i + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
