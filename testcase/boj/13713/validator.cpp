#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement gives only the length of S, not its alphabet, so accept any non-empty line without whitespace.
    string s = inf.readLine("[^]{1,1000000}", "S");
    int n = (int)s.size();
    for (int pos = 0; pos < n; ++pos) {
        ensuref(!isspace((unsigned char)s[pos]), "S must be a single token without whitespace");
    }

    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int query = 1; query <= m; ++query) {
        int i = inf.readInt(1, n, "i");
        inf.readEoln();
    }

    inf.readEof();
}
