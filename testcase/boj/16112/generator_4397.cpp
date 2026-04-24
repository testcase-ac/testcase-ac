#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of quests (small for hand-check)
    int n = rnd.next(1, 10);

    // Hyper-parameter: skew for k (active stones) to get edge k=1 or k=n
    vector<int> kSkews = {0, 1, -1};
    int kSkew = rnd.any(kSkews);
    int k;
    if (kSkew == 0) {
        k = rnd.next(1, n);
    } else {
        // rnd.wnext(hi, t) yields [0..hi-1], so +1 gives [1..n]
        k = rnd.wnext(n, kSkew) + 1;
    }

    // Hyper-parameter: choose value range type for a_i
    // 0 = small [1..100], 1 = medium [1..10000], 2 = full [1..1e8]
    int rangeType = rnd.next(0, 2);
    int rangeMax = (rangeType == 0 ? 100 : (rangeType == 1 ? 10000 : 100000000));

    // Hyper-parameter: skew type for a_i distribution
    // 0 = uniform, 1 = skew to high, -1 = skew to low
    vector<int> skewChoices = {0, 1, -1};
    int skewType = rnd.any(skewChoices);

    // Generate quest rewards a_i in [1..rangeMax]
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (skewType == 0) {
            a[i] = rnd.next(1, rangeMax);
        } else {
            // rnd.wnext(rangeMax, skewType) -> [0..rangeMax-1], then +1
            a[i] = rnd.wnext(rangeMax, skewType) + 1;
        }
    }

    // Output
    println(n, k);
    println(a);

    return 0;
}
