#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 3, "k");
    inf.readEoln();

    // Read n lines of (t_i, w_i)
    for (int i = 0; i < n; i++) {
        inf.readInt(40, 100, "t_i");
        inf.readSpace();
        inf.readInt(0, 100, "w_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
