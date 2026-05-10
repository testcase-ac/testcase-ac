#include "testlib.h"
#include <vector>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read c_1 ... c_N
    vector<int> c = inf.readInts(N, 1, 50000, "c_i");
    inf.readEoln();

    // Global property: according to problem, an arrangement into some number of valid
    // "떡국 그릇 탑" (stacks of strictly decreasing sizes from bottom to top) always exists.
    // For arbitrary sequence with bounds given, this is always true, but we can still
    // compute the theoretically minimal number of such stacks and ensure it fits in int.
    // Also, we implicitly check that input is not absurd by doing this computation.

    // We interpret the problem: each bowl can go on top of a strictly larger bowl.
    // We want to minimize number of stacks. This is equivalent to a greedy process:
    // sort stacks by top size; for each bowl size x in given order, place it on the stack
    // whose top is the smallest value > x, or create new stack if none.
    // We'll implement that and ensure the result is in a safe range.

    // Use map<top_size, count_of_stacks> for multiset-like behavior with upper_bound.
    map<int, int> tops;
    long long stackCount = 0;

    for (int i = 0; i < N; ++i) {
        int x = c[i];
        auto it = tops.upper_bound(x); // first top > x
        if (it == tops.end()) {
            // create new stack with top x
            tops[x]++;
            stackCount++;
        } else {
            // use this stack: decrease count of old top, possibly erase
            int oldTop = it->first;
            if (--(it->second) == 0)
                tops.erase(it);
            // new top is x
            tops[x]++;
        }
    }

    // Sanity: minimal number of stacks must be between 1 and N
    ensuref(stackCount >= 1 && stackCount <= N,
            "Computed minimal stack count out of expected range: %lld (N=%d)",
            stackCount, N);

    inf.readEof();
}
