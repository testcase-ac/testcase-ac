#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<int> a(5);
    long long sum = 0;
    for (int i = 0; i < 5; i++) {
        // Read one number per line, must be between 10 and 90 inclusive
        a[i] = inf.readInt(10, 90, "x_i");
        inf.readEoln();
        // Must be a multiple of 10
        ensuref(a[i] % 10 == 0,
                "Number at line %d is not a multiple of 10: %d", i+1, a[i]);
        sum += a[i];
    }

    // The problem statement guarantees the average is a natural number;
    // i.e., sum must be divisible by 5.
    ensuref(sum % 5 == 0,
            "Sum of inputs (%lld) is not divisible by 5, average would not be integer", sum);

    inf.readEof();
    return 0;
}
