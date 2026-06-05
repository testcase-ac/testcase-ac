#include "testlib.h"

#include <string>

using namespace std;

bool isProbabilityToken(const string& token) {
    if (token.size() != 4 || token[1] != '.') {
        return false;
    }

    if (token[0] == '0') {
        return token[2] >= '0' && token[2] <= '9' && token[3] >= '0' && token[3] <= '9';
    }

    return token == "1.00";
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string p = inf.readToken("[^]+", "p_i");
        ensuref(isProbabilityToken(p), "p_%d must be a probability with exactly two decimal places: %s",
                i, p.c_str());

        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
