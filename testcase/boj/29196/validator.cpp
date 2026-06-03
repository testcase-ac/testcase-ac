#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string k = inf.readToken("0\\.[0-9]{1,8}", "k");
    inf.readEoln();

    ensuref(k.back() != '0', "k has unnecessary trailing zero: %s", k.c_str());

    bool hasNonZeroDigit = false;
    for (int i = 2; i < (int)k.size(); ++i) {
        hasNonZeroDigit |= k[i] != '0';
    }
    ensuref(hasNonZeroDigit, "k must be greater than 0: %s", k.c_str());

    inf.readEof();
}
