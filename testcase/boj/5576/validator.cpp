#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There is exactly one test case with 20 lines: 10 for W, then 10 for K.
    for (int i = 1; i <= 10; i++) {
        // W university score line i
        inf.readInt(0, 100, ("W_score_" + to_string(i)).c_str());
        inf.readEoln();
    }
    for (int i = 1; i <= 10; i++) {
        // K university score line i
        inf.readInt(0, 100, ("K_score_" + to_string(i)).c_str());
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
