#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A, B, C on the first line
    int A = inf.readInt(1, 100000, "A");
    inf.readSpace();
    int B = inf.readInt(1, A, "B");       // 1 ≤ B ≤ A
    inf.readSpace();
    int C = inf.readInt(1, 100000, "C");  // 1 ≤ C ≤ 100000
    inf.readEoln();

    // No further global constraints to check:
    // For these ranges, the equation A*x + B*sin(x) = C always has exactly one real solution.

    inf.readEof();
    return 0;
}
