#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "n");
    inf.readEoln();

    vector<int> seats = inf.readInts(n, 0, 100000, "a_i");
    inf.readEoln();

    int total = accumulate(seats.begin(), seats.end(), 0);
    ensuref(total <= 100000, "total seats must not exceed 100000: %d", total);
    // CHECK: The Korean input section omits this, but the English variant states
    // that the total number of seats is positive.
    ensuref(total > 0, "total seats must be positive");

    inf.readEof();
}
