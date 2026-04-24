#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Read N: number of players
        int N = inf.readInt(1, 10000, "N");
        inf.readEoln();

        // Read the nomination array A_i
        for (int i = 1; i <= N; ++i) {
            inf.readInt(1, N, "A_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
