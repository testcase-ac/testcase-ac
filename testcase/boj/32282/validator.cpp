#include "testlib.h"
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case (problem statement does not mention multiple cases).
    // First line: X Y c
    int X = inf.readInt(-10000, 10000, "X");
    inf.readSpace();
    int Y = inf.readInt(-10000, 10000, "Y");
    inf.readSpace();
    int c = inf.readInt(1, 10000, "c");
    inf.readEoln();

    // No further global properties are guaranteed in the statement
    // (e.g., always reachable in ≤ K steps is not stated), so we do not
    // simulate or verify any reachability/answer-bounded conditions.

    inf.readEof();
}
