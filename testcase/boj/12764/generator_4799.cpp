#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of people
    int N = rnd.next(1, 10);

    // Decide a small range [0..R] from which we pick 2N distinct times
    int minR = 2 * N;
    int maxR = rnd.next(minR, minR + 10);

    // Build a pool of times 0..maxR, shuffle and pick first 2N distinct times
    vector<int> pool(maxR + 1);
    iota(pool.begin(), pool.end(), 0);
    shuffle(pool.begin(), pool.end());
    vector<int> T(pool.begin(), pool.begin() + 2 * N);

    // Optional small offset to shift all times
    int offset = rnd.next(0, 5);
    for (int &t : T) t += offset;

    // Sort times so that T[0..N-1] < T[N..2N-1]
    sort(T.begin(), T.end());

    // Build intervals: for each i, P = T[i], Q = T[N+i]
    vector<pair<int,int>> intervals;
    for (int i = 0; i < N; i++) {
        intervals.emplace_back(T[i], T[N + i]);
    }

    // Shuffle output order for extra randomness
    shuffle(intervals.begin(), intervals.end());

    // Emit the test case
    println(N);
    for (auto &pr : intervals) {
        println(pr.first, pr.second);
    }

    return 0;
}
