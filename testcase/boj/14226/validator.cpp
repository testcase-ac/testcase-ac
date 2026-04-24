#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read S: number of emoticons to achieve
    // Constraint: 2 ≤ S ≤ 1000
    int S = inf.readInt(2, 1000, "S");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
