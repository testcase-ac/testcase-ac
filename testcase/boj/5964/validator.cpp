#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even for a balanced parenthesis string: %d", n);

    int balance = 0;
    for (int i = 1; i <= n; ++i) {
        int token = inf.readInt(0, 1, "paren_i");
        inf.readEoln();

        if (token == 0) {
            ++balance;
        } else {
            --balance;
        }

        ensuref(balance >= 0, "prefix ending at index %d has negative balance", i);
    }

    ensuref(balance == 0, "parenthesis string must be balanced, final balance is %d", balance);
    inf.readEof();
}
