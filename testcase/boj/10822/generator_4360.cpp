#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for number of numbers: bias towards small or large counts
    int n;
    if (rnd.next() < 0.5)
        n = rnd.wnext(10, 1) + 1;   // tends to larger counts near 10
    else
        n = rnd.wnext(10, -1) + 1;  // tends to smaller counts near 1

    // Generate numbers with mixed magnitudes
    vector<int> nums;
    for (int i = 0; i < n; i++) {
        double p = rnd.next();
        int x;
        if (p < 0.4)
            x = rnd.next(1, 9);            // small 1-digit
        else if (p < 0.8)
            x = rnd.next(10, 999);         // medium 2-3 digits
        else
            x = rnd.next(1000, 1000000);   // large up to 1e6
        nums.push_back(x);
    }

    // Occasionally sort ascending or descending for pattern diversity
    double q = rnd.next();
    if (q < 0.33)
        sort(nums.begin(), nums.end());
    else if (q < 0.66)
        sort(nums.begin(), nums.end(), greater<int>());

    // Build comma-separated string S
    string s;
    for (int i = 0; i < n; i++) {
        s += to_string(nums[i]);
        if (i + 1 < n) s += ",";
    }

    // Output the generated test case
    println(s);
    return 0;
}
