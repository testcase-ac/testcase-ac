#include "testlib.h"
#include <vector>
#include <numeric>    // Not strictly needed here, but often useful
#include <algorithm>  // For shuffle
#include <set>        // Could be used for uniqueness, but loop avoids duplicates

using namespace std;

int main(int argc, char* argv[]) {
    // Initialize testlib's random number generator
    registerGen(argc, argv, 1);

    // --- Hyperparameters ---

    // 1. Maximum N for small, verifiable test cases
    //    Problem constraint N >= 2. Let's set a small upper bound.
    int max_n = 10;
    // Ensure generated N is within [2, max_n]
    int n = rnd.next(2, max_n);

    // 2. Probability for a stone (between 2 and N-1) to be small (an obstacle)
    //    This controls the density of obstacles 'M'.
    //    rnd.next() generates double in [0.0, 1.0)
    //    Let's set a max probability, e.g., 0.7 to avoid overly dense obstacles often.
    double bad_stone_prob = rnd.next(0.0, 0.7);

    // --- Generate Test Case ---

    vector<int> bad_stones;
    int potential_bad_stone_count = 0;
    if (n > 2) { // Stones 2 to N-1 are potential candidates for being small
        potential_bad_stone_count = n - 1 - 2 + 1; // = n - 2

        for (int i = 2; i <= n - 1; ++i) {
            if (rnd.next() < bad_stone_prob) {
                bad_stones.push_back(i);
            }
        }
    }

    // Determine the actual number of bad stones generated
    int m = bad_stones.size();

    // --- Validate Constraints ---
    // Ensure M does not exceed the maximum possible (N-2)
    // This check is important especially if bad_stone_prob is high.
    int max_m = 0;
    if (n >= 2) {
        max_m = n - 2;
    }
    
    // If we generated more bad stones than allowed, shuffle and truncate
    if (m > max_m) {
        shuffle(bad_stones.begin(), bad_stones.end());
        m = max_m; // Cap M at the maximum allowed value
        bad_stones.resize(m); // Remove excess stones
    }
    // Ensure M is not negative (shouldn't happen here, but defensive)
    if (m < 0) {
        m = 0; 
    }


    // --- Print Output ---

    // Print N and the final M
    println(n, m);

    // Shuffle the bad stones before printing for random output order
    shuffle(bad_stones.begin(), bad_stones.end());

    // Print the M bad stone numbers
    for (int stone : bad_stones) {
        println(stone);
    }

    return 0;
}
