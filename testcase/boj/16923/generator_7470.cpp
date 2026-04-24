#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: skew length distribution
    int t_pick = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int n = rnd.wnext(26, t_pick) + 1;  // length between 1 and 26

    // Pick a random subset of distinct letters
    vector<char> pool;
    for (char c = 'a'; c <= 'z'; ++c) pool.push_back(c);
    shuffle(pool.begin(), pool.end());
    vector<char> v(pool.begin(), pool.begin() + n);

    // Choose pattern type for variability
    vector<int> types = {0, 1, 2};
    if (n >= 2) types.push_back(3);
    int type = rnd.any(types);

    // Apply pattern
    if (type == 0) {
        // ascending
        sort(v.begin(), v.end());
    } else if (type == 1) {
        // descending
        sort(v.begin(), v.end(), greater<char>());
    } else if (type == 2) {
        // fully random
        shuffle(v.begin(), v.end());
    } else {
        // mixed: prefix ascending, suffix descending
        sort(v.begin(), v.end());
        int k = rnd.next(1, n - 1);
        vector<char> suffix(v.begin() + k, v.end());
        sort(suffix.begin(), suffix.end(), greater<char>());
        v.erase(v.begin() + k, v.end());
        v.insert(v.end(), suffix.begin(), suffix.end());
    }

    // Build and output the string
    string s;
    s.reserve(n);
    for (char c : v) s.push_back(c);
    println(s);

    return 0;
}
