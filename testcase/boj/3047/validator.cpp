#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three numbers on the first line
    vector<int> nums = inf.readInts(3, 1, 100, "number");
    inf.readEoln();

    // They must be distinct and form A < B < C when sorted
    ensuref(nums[0] != nums[1] && nums[0] != nums[2] && nums[1] != nums[2],
            "All three numbers must be distinct");
    vector<int> sorted = nums;
    sort(sorted.begin(), sorted.end());
    ensuref(sorted[0] < sorted[1] && sorted[1] < sorted[2],
            "The three numbers must satisfy A < B < C when sorted");

    // Read the permutation string on the second line
    string order = inf.readToken("[ABC]{3}", "order");
    inf.readEoln();

    // Check that it is a permutation of 'A', 'B', 'C'
    bool seenA = false, seenB = false, seenC = false;
    for (int i = 0; i < 3; i++) {
        char c = order[i];
        if (c == 'A') {
            ensuref(!seenA, "Duplicate 'A' in order");
            seenA = true;
        } else if (c == 'B') {
            ensuref(!seenB, "Duplicate 'B' in order");
            seenB = true;
        } else if (c == 'C') {
            ensuref(!seenC, "Duplicate 'C' in order");
            seenC = true;
        } else {
            // This should not happen because regex restricts characters,
            // but we keep it for completeness.
            ensuref(false, "Invalid character '%c' in order", c);
        }
    }
    ensuref(seenA && seenB && seenC,
            "Order must contain each of 'A', 'B', 'C' exactly once");

    inf.readEof();
    return 0;
}
