#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

// Simulate the game to ensure constraints like "answer always exists" etc.
// Here, it's mainly to check that values never exceed reasonable bounds.
// We'll also compute max value just to check for overflow issues.
int simulateMaxValue(const vector<int>& a) {
    // The exact game rules are not formally specified beyond merging equal
    // adjacent numbers into +1, but there's no statement guarantee like
    // "answer <= X" that must be validated. However, we can still sanity-check
    // that values never explode beyond what is implied.
    //
    // In worst case, merging equal numbers repeatedly can increase value at
    // most by log2(N), starting from <=40. With N <= 262,144, that's <= 40+18.
    // We'll use this as a loose upper bound to flag obviously broken tests.

    const int n = (int)a.size();
    vector<int> b = a;
    int maxv = 0;
    for (int x : b) maxv = max(maxv, x);

    bool changed = true;
    int safetySteps = 0;
    // Extremely naive O(N^2) merging simulation with a safety step cap.
    // This is acceptable inside a validator.
    while (changed && safetySteps <= 1000000) {
        changed = false;
        ++safetySteps;
        vector<int> nxt;
        for (int i = 0; i < (int)b.size();) {
            if (i + 1 < (int)b.size() && b[i] == b[i + 1]) {
                int merged = b[i] + 1;
                nxt.push_back(merged);
                maxv = max(maxv, merged);
                i += 2;
                changed = true;
            } else {
                nxt.push_back(b[i]);
                ++i;
            }
        }
        b.swap(nxt);
    }

    // Sanity: values shouldn't exceed 60 (very generous).
    ensuref(maxv <= 60, "Value after merges too large (%d). Likely invalid test.", maxv);
    // Sanity: safety steps not exceeded (avoid pathological validator bugs).
    ensuref(safetySteps <= 1000000, "Too many merge steps in validator simulation.");

    return maxv;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N lines with integers follow.
    // From problem: "1 이상 40 이하의 정수 N(2 ≤ N ≤ 262,144)개로 이루어진 수열"
    // Means:
    // - There are N integers.
    // - Each integer is between 1 and 40 inclusive.
    // N itself satisfies 2 ≤ N ≤ 262,144.

    int N = inf.readInt(2, 262144, "N");
    inf.readEoln();

    vector<int> a;
    a.reserve(N);

    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(1, 40, "a_i");
        inf.readEoln();
        a.push_back(x);
    }

    // No explicit global property like connectivity, etc.
    // But we can still sanity-check the game behavior as per instructions.
    simulateMaxValue(a);

    inf.readEof();
}
