#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of players
    int N = rnd.next(3, 10);

    // Prepare a pool of distinct skill values
    int MaxV = rnd.next(N, 20);
    vector<int> pool(MaxV);
    iota(pool.begin(), pool.end(), 1);
    shuffle(pool.begin(), pool.end());
    vector<int> skills(pool.begin(), pool.begin() + N);

    // Choose a pattern for diversity
    int pattern = rnd.next(0, 3);
    if (pattern == 1) {
        // strictly increasing
        sort(skills.begin(), skills.end());
    } else if (pattern == 2) {
        // strictly decreasing
        sort(skills.begin(), skills.end(), greater<int>());
    } else if (pattern == 3) {
        // bitonic-like: prefix ascending, suffix descending
        int p = rnd.next(2, N - 1);
        sort(skills.begin(), skills.begin() + p);
        sort(skills.begin() + p, skills.end(), greater<int>());
    }
    // pattern == 0: fully random, do nothing

    // Output
    println(N);
    for (int x : skills) println(x);

    return 0;
}
