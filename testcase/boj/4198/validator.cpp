#include "testlib.h"
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 2000, "n");
    inf.readEoln();

    set<int> weights;
    for (int i = 0; i < n; ++i) {
        // CHECK: The statement gives no upper bound for non-negative integer weights;
        // cap them at signed 32-bit int range for a practical testcase.ac validator.
        int weight = inf.readInt(0, 2147483647, "weight");
        inf.readEoln();
        ensuref(weights.insert(weight).second,
                "weights must be distinct, but %d appears more than once",
                weight);
    }

    inf.readEof();
}
