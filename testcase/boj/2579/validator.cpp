#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of stairs: natural number up to 300
    int n = inf.readInt(1, 300, "n");
    inf.readEoln();

    // Each stair score: natural number up to 10000
    for (int i = 1; i <= n; i++) {
        // We name each score parameter for clarity in error messages
        string name = "score_" + to_string(i);
        inf.readInt(1, 10000, name.c_str());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
