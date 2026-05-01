#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; tc++) {
        // Hyper-parameter for k: bias small or large
        int bias = rnd.any(vector<int>{-2, -1, 0, 1, 2});
        int k = rnd.wnext(6, bias) + 7;  // yields [7..12] with bias

        vector<int> S;
        // Hyper-parameter: uniform vs clustered selection
        if (rnd.next() < 0.5) {
            int pivot = rnd.next(1, 49);
            int H = rnd.next(3, 15);
            int L = max(1, pivot - H);
            int R = min(49, pivot + H);
            if (R - L + 1 >= k) {
                vector<int> pool;
                for (int x = L; x <= R; x++) pool.push_back(x);
                shuffle(pool.begin(), pool.end());
                S.assign(pool.begin(), pool.begin() + k);
            } else {
                // fallback to uniform
                vector<int> pool(49);
                iota(pool.begin(), pool.end(), 1);
                shuffle(pool.begin(), pool.end());
                S.assign(pool.begin(), pool.begin() + k);
            }
        } else {
            // uniform selection
            vector<int> pool(49);
            iota(pool.begin(), pool.end(), 1);
            shuffle(pool.begin(), pool.end());
            S.assign(pool.begin(), pool.begin() + k);
        }

        sort(S.begin(), S.end());
        // Output one test case
        printf("%d", k);
        for (int x : S) printf(" %d", x);
        printf("\n");
    }
    // terminating zero
    printf("0\n");
    return 0;
}
