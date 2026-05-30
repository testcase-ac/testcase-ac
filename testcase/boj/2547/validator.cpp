#include "testlib.h"

#include <string>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxT = 100000;
    const int maxN = 100000;
    const long long maxCandy = 1000000000000000000LL;

    int t = inf.readInt(1, maxT, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        std::string blank = inf.readLine("[^]*", "blank_line");
        ensuref(blank.empty(), "test case %d must be preceded by a blank line", tc);

        int n = inf.readInt(1, maxN, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readLong(0LL, maxCandy, "c_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
