#include "testlib.h"
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose small or medium N
    int N;
    if (rnd.next(0, 1) == 0) {
        N = rnd.next(5, 10);
    } else {
        N = rnd.next(20, 30);
    }

    // Hyper-parameter: choose base number range
    int maxVal;
    if (rnd.next(0, 1) == 0) {
        // moderate range
        maxVal = rnd.next(N * 10, max( N * 10, N * 100 ));
    } else {
        // larger range
        maxVal = rnd.next(max(N * 100, 100), max(N * 1000, 1000));
    }

    int M = N - 1; // we'll add one special sum
    unordered_set<int> seen;
    vector<int> base;
    base.reserve(M);

    // Generate M unique base values
    while ((int)base.size() < M) {
        int x = rnd.next(1, maxVal);
        if (!seen.count(x)) {
            seen.insert(x);
            base.push_back(x);
        }
    }
    sort(base.begin(), base.end());

    // Compute a guaranteed sum using the three largest base elements
    long long S = 0;
    int sz = base.size();
    // pick the last three elements
    S = (long long)base[sz-1] + base[sz-2] + base[sz-3];
    // S > maxVal guaranteed, so unique

    // Build U = base + S
    vector<long long> U;
    U.reserve(N);
    for (int x : base) U.push_back(x);
    U.push_back(S);

    // Shuffle to avoid sorted order
    shuffle(U.begin(), U.end());

    // Output
    println(N);
    for (auto x : U) {
        println(x);
    }
    return 0;
}
