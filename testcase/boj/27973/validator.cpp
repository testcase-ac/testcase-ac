#include "testlib.h"

using namespace std;

const long long MAX_Q = 170000;
const long long MAX_ADD = 100000;
const long long MAX_MUL = 100;
const long long MAX_REMOVE = 100000000;
const __int128 INITIAL_MAX = 1234567890123LL;
const __int128 REMOVE_SUM_LIMIT = 1234567890120LL;
const __int128 VALUE_LIMIT = 1000000000000000000LL;

void ensureValueBounds(__int128 first, __int128 mul, __int128 add, int commandIndex) {
    __int128 minValue = first * mul + add;
    __int128 maxValue = INITIAL_MAX * mul + add;
    ensuref(-VALUE_LIMIT <= minValue && minValue <= VALUE_LIMIT,
            "minimum value is out of bounds after command %d", commandIndex);
    ensuref(-VALUE_LIMIT <= maxValue && maxValue <= VALUE_LIMIT,
            "maximum value is out of bounds after command %d", commandIndex);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, MAX_Q, "Q");
    inf.readEoln();

    __int128 first = 1;
    __int128 mul = 1;
    __int128 add = 0;
    __int128 removed = 0;

    for (int i = 1; i <= q; ++i) {
        int op = inf.readInt(0, 3, "op");
        if (op == 0) {
            inf.readSpace();
            int x = inf.readInt(-MAX_ADD, MAX_ADD, "x");
            inf.readEoln();
            add += x;
        } else if (op == 1) {
            inf.readSpace();
            int x = inf.readInt(1, MAX_MUL, "x");
            inf.readEoln();
            mul *= x;
            add *= x;
        } else if (op == 2) {
            inf.readSpace();
            int n = inf.readInt(1, MAX_REMOVE, "n");
            inf.readEoln();
            removed += n;
            ensuref(removed <= REMOVE_SUM_LIMIT,
                    "sum of removed elements exceeds limit after command %d", i);
            first += n;
        } else {
            inf.readEoln();
        }

        ensureValueBounds(first, mul, add, i);
        if (i == q) {
            ensuref(op == 3, "last command must be 3");
        }
    }

    inf.readEof();
}
