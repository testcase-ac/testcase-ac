#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(2, 10, "q");
    inf.readSpace();
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int d = inf.readInt(1, 2 * n, "D");
    inf.readEoln();

    string alphabet;
    for (int digit = 0; digit < q; ++digit) {
        alphabet += char('0' + digit);
    }
    string pattern = "[" + alphabet + "]{" + to_string(n) + "," + to_string(n) + "}";

    inf.readToken(pattern, "f1");
    inf.readEoln();
    inf.readToken(pattern, "f2");
    inf.readEoln();
    inf.readEof();
}
