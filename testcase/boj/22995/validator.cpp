#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // 2. Read K
        int K = inf.readInt(1, 262143, "K"); // 1 <= K < 262144
        inf.readEoln();
    }

    inf.readEof();
}
