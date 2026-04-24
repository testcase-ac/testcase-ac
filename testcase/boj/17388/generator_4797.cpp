#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide whether to generate an "OK" case (sum >= 100) or a "pressure" case (sum < 100)
    bool wantOK = rnd.next() < 0.7;

    // Weight parameter to bias values toward low, mid, or high ends
    vector<int> weights = {-2, -1, 0, 1, 2};
    int t = rnd.any(weights);

    int S, K, H;
    while (true) {
        // Generate participation values in [0,100], biased by t
        S = rnd.wnext(101, t);
        K = rnd.wnext(101, t);
        H = rnd.wnext(101, t);
        // Must be distinct
        if (S == K || S == H || K == H) continue;
        int sum = S + K + H;
        // Check desired sum condition
        if ((wantOK && sum >= 100) || (!wantOK && sum < 100))
            break;
    }

    // Output the three distinct participation values
    println(S, K, H);
    return 0;
}
