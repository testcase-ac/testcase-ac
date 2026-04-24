#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read N: 2 < N < 500000  => 3 <= N <= 499999
    int N = inf.readInt(3, 499999, "N");
    inf.readEoln();
    
    // Each of the next N lines: the label accused by player i
    for (int i = 1; i <= N; i++) {
        int accused = inf.readInt(1, N, "accused");
        inf.readEoln();
        ensuref(accused != i,
                "Player %d cannot accuse themselves (accused = %d)", i, accused);
    }
    
    inf.readEof();
    return 0;
}
