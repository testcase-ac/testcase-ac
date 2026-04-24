#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test values
    int T = rnd.next(1, 10);
    // Maximum digit length for each value
    int maxLen = rnd.next(1, 20);
    // Decide if we use weighted lengths or uniform
    bool useWeighted = rnd.next(0, 1);
    // If weighted, pick a weight parameter
    vector<int> wOpts = {-3, -1, 1, 3};
    int w = useWeighted ? rnd.any(wOpts) : 0;

    vector<string> nums;
    nums.reserve(T);
    for (int i = 0; i < T; i++) {
        int L;
        if (useWeighted) {
            // weighted in [0, maxLen-1], then +1 to get [1, maxLen]
            L = rnd.wnext(maxLen, w) + 1;
        } else {
            L = rnd.next(1, maxLen);
        }
        // build a positive integer of length L, no leading zero
        string s;
        s += char('1' + rnd.next(0, 8)); // first digit [1-9]
        for (int j = 1; j < L; j++) {
            s += char('0' + rnd.next(0, 9));
        }
        nums.push_back(s);
    }

    // Output the generated numbers, then the terminator 0
    for (auto &s : nums) {
        println(s);
    }
    println(0);

    return 0;
}
