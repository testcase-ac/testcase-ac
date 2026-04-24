#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: number of participants (1 to 10)
    int n = rnd.next(1, 10);
    // Prepare some distinct participant names
    vector<string> pool = {
        "Alice", "Bob", "Carol", "Dave", "Eve", "Frank", "Grace",
        "Heidi", "Ivan", "Judy", "Mallory", "Niaj", "Olivia",
        "Peggy", "Sybil", "Trent"
    };
    shuffle(pool.begin(), pool.end());
    vector<string> names(pool.begin(), pool.begin() + n);
    // Generate bids following doubling rule
    vector<int64_t> bets(n);
    bets[0] = rnd.next(1, 99); // initial bid
    int64_t current_max = bets[0];
    for (int i = 1; i < n; i++) {
        // factor between 2 and 5
        int f = rnd.next(2, 5);
        bets[i] = current_max * f;
        current_max = max(current_max, bets[i]);
    }
    // Decide if there is a winning subset
    bool has_solution = rnd.next(0, 9) < 7; // 70% chance of solution
    int64_t s_val;
    if (has_solution) {
        // pick a random non-empty subset
        int k = rnd.next(1, n);
        vector<int> idx(n);
        for (int i = 0; i < n; i++) idx[i] = i;
        shuffle(idx.begin(), idx.end());
        s_val = 0;
        for (int i = 0; i < k; i++) {
            s_val += bets[idx[i]];
        }
    } else {
        // make s greater than total sum to ensure no subset sums to s
        int64_t sum_all = 0;
        for (auto b: bets) sum_all += b;
        s_val = sum_all + rnd.next(1, 10);
    }
    // Output
    println(n, to_string(s_val));
    for (int i = 0; i < n; i++) {
        println(names[i], to_string(bets[i]));
    }
    return 0;
}
