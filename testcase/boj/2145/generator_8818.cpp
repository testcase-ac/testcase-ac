#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> nums;
    int style = rnd.next(0, 2);

    if (style == 0) {
        // Small random test, few numbers
        int T = rnd.next(1, 5);
        nums.reserve(T);
        for (int i = 0; i < T; ++i) {
            nums.push_back(rnd.next(1, 1000)); // 1 to 3 digits
        }
        // Ensure at least one single-digit
        bool hasSingle = false;
        for (int x : nums) if (x < 10) { hasSingle = true; break; }
        if (!hasSingle) {
            int pos = rnd.next(0, T - 1);
            nums[pos] = rnd.next(1, 9);
        }
    } else if (style == 1) {
        // Mixed with various patterns
        nums = {1, 9, 10, 11, 99, 1000};
        int extra = rnd.next(0, 5);
        for (int i = 0; i < extra; ++i) {
            nums.push_back(rnd.next(1, 99999)); // up to 5 digits
        }
    } else {
        // Many numbers with digital root 9 and extras
        vector<int> base = {8, 18, 27, 36, 45, 54, 63, 72, 81, 90};
        int keep = rnd.next(3, (int)base.size());
        base.resize(keep);
        nums = base;
        int extra = rnd.next(0, 3);
        for (int i = 0; i < extra; ++i) {
            nums.push_back(rnd.next(1, 99999));
        }
    }

    // Occasionally add the maximum value edge case
    if (rnd.next(0, 1) == 1 && (int)nums.size() < 20) {
        nums.push_back(99999);
    }

    // Shuffle for randomness
    shuffle(nums.begin(), nums.end());

    // Output all numbers, one per line, then the terminating 0
    for (int x : nums) {
        println(x);
    }
    println(0);

    return 0;
}
