#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T, assume 1 <= T <= 100000 as per global constraints
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Each control program is a non-empty string of commands {F,B,L,R}, length up to 500
        // No spaces allowed, so read as a single token
        inf.readToken("[FBLR]{1,500}", "program");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
