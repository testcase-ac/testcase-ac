#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of paintings
    int N = rnd.next(1, 10);

    // Hyper-parameter: choose a mode for heights
    int hmode = rnd.next(0, 2);
    vector<int> H;
    if (hmode == 0) {
        // uniform random heights
        for (int i = 0; i < N; i++) {
            H.push_back(rnd.next(1, 50));
        }
    } else if (hmode == 1) {
        // increasing heights with small increments
        int cur = rnd.next(1, 5);
        for (int i = 0; i < N; i++) {
            H.push_back(cur);
            int inc = rnd.next(1, 10);
            cur = min(cur + inc, 50);
        }
    } else {
        // clustered heights: pick few distinct bases
        int k = rnd.next(1, min(3, N));
        vector<int> bases;
        for (int i = 0; i < k; i++) {
            bases.push_back(rnd.next(1, 50));
        }
        for (int i = 0; i < N; i++) {
            H.push_back(rnd.any(bases));
        }
    }

    // Ensure all heights >= 1
    for (int &x : H) if (x < 1) x = 1;

    // Determine S so that 1 <= S <= min(H)
    int minH = *min_element(H.begin(), H.end());
    int S = rnd.next(1, minH);

    // Hyper-parameter: choose a mode for costs
    vector<int> C(N);
    int cmode = rnd.next(0, 1);
    if (cmode == 0) {
        // uniform costs
        for (int i = 0; i < N; i++) {
            C[i] = rnd.next(1, 500);
        }
    } else {
        // clustered costs: few distinct values
        int k = rnd.next(1, min(3, N));
        vector<int> cb;
        for (int i = 0; i < k; i++) {
            cb.push_back(rnd.next(1, 500));
        }
        for (int i = 0; i < N; i++) {
            C[i] = rnd.any(cb);
        }
    }

    // Shuffle the painting order
    vector<int> idx(N);
    for (int i = 0; i < N; i++) idx[i] = i;
    shuffle(idx.begin(), idx.end());

    // Output
    println(N, S);
    for (int i = 0; i < N; i++) {
        int p = idx[i];
        println(H[p], C[p]);
    }

    return 0;
}
