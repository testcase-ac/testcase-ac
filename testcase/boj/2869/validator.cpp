#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A, B, V with given constraints: 1 ≤ B < A ≤ V ≤ 1e9
    // From 1 ≤ B < A, we infer A ≥ 2.
    int A = inf.readInt(2, 1000000000, "A");
    inf.readSpace();
    int B = inf.readInt(1, A - 1, "B");
    inf.readSpace();
    int V = inf.readInt(A, 1000000000, "V");
    inf.readEoln();
    
    inf.readEof();
    return 0;
}
