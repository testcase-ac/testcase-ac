#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[()]{2,200000}", "S");
    inf.readEoln();

    int balance = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == '(') {
            ++balance;
        } else {
            --balance;
        }
        ensuref(balance >= 0, "prefix balance is negative at position %d", i + 1);
    }

    ensuref(balance == 0, "final balance must be zero");

    inf.readEof();
}
