#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N with given constraints
    int M = inf.readInt(2, 100, "M");
    inf.readSpace();
    int N = inf.readInt(2, 100, "N");
    inf.readEoln();
    
    // No extra data
    inf.readEof();
    return 0;
}
