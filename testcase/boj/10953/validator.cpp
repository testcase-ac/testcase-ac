#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; cap it at a practical
    // testcase count for this small numeric format.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        string line = inf.readToken("[1-9],[1-9]", "case");
        inf.readEoln();
        ensuref(line.size() == 3, "case %d must be exactly A,B", i);
    }

    inf.readEof();
}
