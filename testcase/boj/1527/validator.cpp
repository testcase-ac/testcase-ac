#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B according to constraints: 1 ≤ A ≤ B ≤ 10^9
    int A = inf.readInt(1, 1000000000, "A");
    inf.readSpace();
    int B = inf.readInt(A, 1000000000, "B");
    inf.readEoln();
    
    inf.readEof();
    return 0;
}
