#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int c = inf.readInt(1, 100000, "C");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000000LL, "K");
    inf.readEoln();

    string letter = inf.readToken("[A-Z]{1,100}", "letter");
    ensuref(static_cast<int>(letter.size()) == n,
            "letter length must be N: expected %d, got %d",
            n,
            static_cast<int>(letter.size()));
    inf.readEoln();

    for (int rule = 1; rule <= c; ++rule) {
        string op = inf.readToken("S|A", "op");
        inf.readSpace();

        if (op == "S") {
            int i = inf.readInt(0, n - 1, "i");
            inf.readSpace();
            int j = inf.readInt(0, n - 1, "j");
            ensuref(i != j, "swap rule %d must use distinct indices: %d == %d", rule, i, j);
        } else {
            inf.readInt(0, n - 1, "i");
            inf.readSpace();
            inf.readInt(1, 25, "x");
        }

        inf.readEoln();
    }

    inf.readEof();
}
