#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 18, "N");
        inf.readSpace();
        int k = inf.readInt(1, n - 1, "K");
        inf.readEoln();

        string digits = inf.readToken("[0-9]{2,18}", "number");
        ensuref((int)digits.size() == n, "number length must be N, found %d", (int)digits.size());
        ensuref(digits[0] != '0', "input number must not have a leading zero");
        inf.readEoln();
    }

    inf.readEof();
}
