#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Number of test cases: 0 < t < 1000
    int t = inf.readInt(1, 999, "t");
    inf.readEoln();
    
    for (int tc = 1; tc <= t; tc++) {
        setTestCase(tc);
        
        // Number of rounds in this test case: 0 < n < 100
        int n = inf.readInt(1, 99, "n");
        inf.readEoln();
        
        // Each round: two moves, each one of 'R', 'P', 'S'
        for (int i = 0; i < n; i++) {
            string p1 = inf.readToken("[RPS]", "player1_move");
            inf.readSpace();
            string p2 = inf.readToken("[RPS]", "player2_move");
            inf.readEoln();
        }
    }
    
    inf.readEof();
    return 0;
}
