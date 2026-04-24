#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        // Number of shops/points
        int N = inf.readInt(1, 100, "N");
        inf.readEoln();
        // Starting position index
        int a = inf.readInt(1, N, "a");
        inf.readEoln();
        // Travel times between adjacent points p_i and p_{i+1}
        for (int i = 1; i <= N - 1; ++i) {
            inf.readInt(1, 15000000, "t");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
