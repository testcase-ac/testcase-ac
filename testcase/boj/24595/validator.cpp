#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    int totalLength = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string n = inf.readLine("[0-9]{1,100000}", "n");
        ensuref(n[0] != '0', "n has leading zero");
        totalLength += static_cast<int>(n.size());
        ensuref(totalLength <= 100000,
                "sum of input lengths exceeds 100000 after case %d", tc);
    }

    inf.readEof();
}
