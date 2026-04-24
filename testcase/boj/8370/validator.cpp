#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the four integers with exact single-space separators
    int n1 = inf.readInt(1, 1000, "n1");
    inf.readSpace();
    int k1 = inf.readInt(1, 1000, "k1");
    inf.readSpace();
    int n2 = inf.readInt(1, 1000, "n2");
    inf.readSpace();
    int k2 = inf.readInt(1, 1000, "k2");
    
    // End of the only line
    inf.readEoln();
    // No extra data
    inf.readEof();

    return 0;
}
