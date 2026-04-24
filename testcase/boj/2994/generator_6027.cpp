#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of members N biased small or large
    int bias = rnd.any(vector<int>{-1, 1});
    int N = rnd.wnext(15, bias) + 1;  // N in [1..15]
    // Ensure total minimal capacity for N intervals of length >=1: T >= ceil(N/2)
    int Tmin = (N + 1) / 2;
    // Randomize T between Tmin and Tmin+20
    int Theap = Tmin + rnd.next(0, 20);
    int T = rnd.next(Tmin, Theap);

    // Prepare two "lanes" (back-to-back scheduling) with remaining times
    int rem0 = T, rem1 = T;
    vector<int> d(N);
    for (int i = 0; i < N; i++) {
        int remItems = N - i;               // including this one
        int remTotal = rem0 + rem1;         // total capacity left
        // max we can take and still leave >=1 per future item
        int maxD = min(max(rem0, rem1), remTotal - (remItems - 1));
        // choose duration in [1..maxD]
        int di = rnd.next(1, maxD);
        // assign to lane with larger remaining (tie-break random)
        int lane;
        if (rem0 == rem1) {
            lane = rnd.next(0,1);
        } else {
            lane = rem0 > rem1 ? 0 : 1;
        }
        if (lane == 0) rem0 -= di;
        else            rem1 -= di;
        d[i] = di;
    }

    // Shuffle order of durations to avoid sorted patterns
    shuffle(d.begin(), d.end());

    // Output
    println(T, N);
    println(d);

    return 0;
}
