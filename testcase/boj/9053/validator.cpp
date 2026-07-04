#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 10, "N");
        inf.readEoln();

        vector<int> t = inf.readInts(N, 1, 10, "t_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
