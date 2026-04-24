#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: number of friends and colors
    int n = rnd.next(2, 10);
    int k = rnd.next(2, 10);

    // Generate days per friend
    vector<int> d(n);
    int sumd = 0;
    for (int i = 0; i < n; i++) {
        d[i] = rnd.next(1, 10);
        sumd += d[i];
    }
    // Total pins needed = 4 * sumd
    int total_needed = 4 * sumd;

    // Choose scenario: under-supplied, exactly supplied, or over-supplied
    int scenario = rnd.next(0, 2);
    if (scenario == 0 && total_needed - 1 < k) {
        // cannot under-supply if we can't allocate at least 1 per color
        scenario = 1;
    }

    // Determine total supply sum
    int total_l_sum;
    if (scenario == 0) {
        // under-supplied: sum in [k, total_needed-1]
        total_l_sum = rnd.next(k, total_needed - 1);
    } else if (scenario == 1) {
        // exactly enough
        total_l_sum = total_needed;
    } else {
        // over-supplied: sum in [total_needed+1, total_needed + 10*k]
        total_l_sum = rnd.next(total_needed + 1, total_needed + 10 * k);
    }

    // Distribute total_l_sum into k positive parts
    vector<int> l(k, 1);
    int rem = total_l_sum - k;
    for (int i = 0; i < rem; i++) {
        int j = rnd.next(0, k - 1);
        l[j]++;
    }
    shuffle(l.begin(), l.end());

    // Output
    println(n, k);
    println(d);
    println(l);

    return 0;
}
