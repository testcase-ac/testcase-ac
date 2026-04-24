#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly 5 integers in one line
    vector<int> a = inf.readInts(5, 1, 5, "a_i");
    inf.readEoln();

    // Check distinctness
    bool seen[6] = {false};
    for (int i = 0; i < 5; i++) {
        int x = a[i];
        ensuref(!seen[x], "Duplicate number detected: %d appears more than once", x);
        seen[x] = true;
    }

    // Check it's a permutation of 1..5
    for (int x = 1; x <= 5; x++) {
        ensuref(seen[x], "Missing number in input: %d is not present", x);
    }

    // Ensure initial order isn't already sorted 1 2 3 4 5
    bool already_sorted = true;
    for (int i = 0; i < 5; i++) {
        if (a[i] != i+1) {
            already_sorted = false;
            break;
        }
    }
    ensuref(!already_sorted, "Initial sequence must not be already sorted 1 2 3 4 5");

    inf.readEof();
    return 0;
}
