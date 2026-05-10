#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are exactly 4 lines, each with one integer t_i (1 <= t_i <= 1800)
    for (int i = 1; i <= 4; ++i) {
        int t = inf.readInt(1, 1800, format("t_%d", i).c_str());
        inf.readEoln();
    }

    inf.readEof();
}
