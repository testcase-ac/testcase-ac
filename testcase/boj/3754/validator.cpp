#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 474, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 47, "N");
        inf.readEoln();

        vector<int> A = inf.readInts(N, 1, 4747, "A_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
