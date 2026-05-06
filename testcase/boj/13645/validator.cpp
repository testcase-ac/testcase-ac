#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    // Read test cases until EOF
    while (!inf.eof()) {
        // Read one sequence of moves: non-empty, up to 80, only F,B,R,L,U,D in either case
        tc++;
        ensuref(tc <= 100000, "Number of test cases exceeds 100000");
        // readToken reads up to whitespace; we then require the line to end immediately
        inf.readToken("[FBRLUDfbrlud]{1,80}", "moves");
        inf.readEoln();
        setTestCase(tc);
    }
    ensuref(tc >= 1, "No test cases found");
    inf.readEof();
    return 0;
}
