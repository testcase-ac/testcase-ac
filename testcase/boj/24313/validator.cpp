#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read coefficients a1 and a0: integers with |a_i| ≤ 100
    int a1 = inf.readInt(-100, 100, "a1");
    inf.readSpace();
    int a0 = inf.readInt(-100, 100, "a0");
    inf.readEoln();

    // Read constant c: positive integer 1 ≤ c ≤ 100
    int c = inf.readInt(1, 100, "c");
    inf.readEoln();

    // Read n0: positive integer 1 ≤ n0 ≤ 100
    int n0 = inf.readInt(1, 100, "n0");
    inf.readEoln();

    // No other constraints to validate for input; solution will check the O(n) condition.
    inf.readEof();
    return 0;
}
