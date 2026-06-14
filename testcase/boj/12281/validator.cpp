#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 30, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        vector<int> s = inf.readInts(N, -1000, 1000, "s_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
