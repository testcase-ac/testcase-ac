#include "testlib.h"
#include <string>
using namespace std;

namespace {

void readProbability(const string& name) {
    string token = inf.readToken("[^\\ ]{1,8}", name);

    ensuref(token[0] == '0' || token[0] == '1',
            "%s must have integer part 0 or 1: %s", name.c_str(), token.c_str());

    if (token.size() == 1) {
        return;
    }

    ensuref(token[1] == '.', "%s has invalid decimal point: %s", name.c_str(),
            token.c_str());
    ensuref(token.size() >= 3 && token.size() <= 8,
            "%s must have 1 to 6 digits after decimal point: %s", name.c_str(),
            token.c_str());

    for (int i = 2; i < int(token.size()); ++i) {
        ensuref('0' <= token[i] && token[i] <= '9',
                "%s has non-digit fractional character: %s", name.c_str(),
                token.c_str());
        if (token[0] == '1') {
            ensuref(token[i] == '0', "%s is greater than 1: %s", name.c_str(),
                    token.c_str());
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 500000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        readProbability("p_i");
        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "coin_i");
        inf.readSpace();
        readProbability("p_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
