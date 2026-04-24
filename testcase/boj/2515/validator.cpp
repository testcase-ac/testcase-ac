#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and S
    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int S = inf.readInt(1, 20000000, "S");
    inf.readEoln();

    // Read each picture's height and price
    for (int i = 0; i < n; i++) {
        int h = inf.readInt(S, 20000000, "H_i");  // H_i >= S
        inf.readSpace();
        int c = inf.readInt(1, 1000, "C_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
