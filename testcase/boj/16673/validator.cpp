#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // C: number of years (0 ≤ C ≤ 100)
    int C = inf.readInt(0, 100, "C");
    inf.readSpace();
    // K: attachment constant (0 ≤ K ≤ 1000)
    int K = inf.readInt(0, 1000, "K");
    inf.readSpace();
    // P: purchase-addiction constant (0 ≤ P ≤ 100)
    int P = inf.readInt(0, 100, "P");
    inf.readEoln();

    // No other global constraints to check.
    inf.readEof();
    return 0;
}
