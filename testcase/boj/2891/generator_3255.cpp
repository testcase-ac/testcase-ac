#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small sizes
    int N = rnd.next(2, 10);
    int S = rnd.next(1, N);
    int R = rnd.next(1, N);

    // Determine feasible overlap between broken and extra
    int lb = max(0, R - (N - S));
    int ub = min(S, R);
    // Bias overlap count to extremes or uniform
    int overlap = rnd.wnext(ub - lb + 1, rnd.next(-1, 1)) + lb;

    // Generate broken teams
    vector<int> nums(N);
    iota(nums.begin(), nums.end(), 1);
    shuffle(nums.begin(), nums.end());
    vector<int> broken(nums.begin(), nums.begin() + S);

    // Pick overlap teams from broken
    vector<int> bro_sh = broken;
    shuffle(bro_sh.begin(), bro_sh.end());
    vector<int> overlapVec(bro_sh.begin(), bro_sh.begin() + overlap);

    // Available for extra without further overlapping
    vector<bool> isBroken(N+1, false);
    for (int x : broken) isBroken[x] = true;
    vector<int> avail;
    for (int i = 1; i <= N; ++i)
        if (!isBroken[i])
            avail.push_back(i);
    shuffle(avail.begin(), avail.end());

    // Build extra list
    vector<int> extra = overlapVec;
    int need = R - overlap;
    for (int i = 0; i < need; ++i)
        extra.push_back(avail[i]);
    shuffle(extra.begin(), extra.end());
    shuffle(broken.begin(), broken.end());

    // Output
    println(N, S, R);
    println(broken);
    println(extra);

    return 0;
}
