#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases
    int T = rnd.next(1, 10);
    vector<int> Uoptions = {10, 20, 50, 99};
    for (int ti = 0; ti < T; ti++) {
        int U = rnd.any(Uoptions);
        // choose list size between 2 and min(15, U)
        int n = rnd.next(2, min(15, U));
        int maxPairs = n / 2;
        // decide how many exact-double pairs to include
        int mode = rnd.next(0, 3);
        int K;
        if (mode == 0) {
            K = 0;
        } else if (mode == 1) {
            K = maxPairs >= 1 ? rnd.next(1, min(2, maxPairs)) : 0;
        } else if (mode == 2) {
            K = maxPairs;
        } else {
            K = rnd.next(0, maxPairs);
        }
        vector<bool> used(U + 1, false);
        vector<int> elems;
        // gather candidate x where 2*x <= U
        vector<int> candX;
        for (int x = 1; x * 2 <= U; x++) {
            candX.push_back(x);
        }
        shuffle(candX.begin(), candX.end());
        // pick up to K disjoint pairs (x, 2*x)
        int takenPairs = 0;
        for (int x : candX) {
            if (takenPairs >= K) break;
            if (used[x] || used[2*x]) continue;
            used[x] = used[2*x] = true;
            elems.push_back(x);
            elems.push_back(2*x);
            takenPairs++;
        }
        // fill remaining with numbers that don't form new pairs
        int need = n - (int)elems.size();
        vector<int> candY;
        for (int y = 1; y <= U; y++) {
            if (used[y]) continue;
            // avoid creating new double relations
            if (y % 2 == 0 && used[y/2]) continue;
            if (y * 2 <= U && used[y*2]) continue;
            candY.push_back(y);
        }
        shuffle(candY.begin(), candY.end());
        for (int i = 0; i < need && i < (int)candY.size(); i++) {
            used[candY[i]] = true;
            elems.push_back(candY[i]);
        }
        // shuffle and terminate with 0
        shuffle(elems.begin(), elems.end());
        elems.push_back(0);
        println(elems);
    }
    // end marker
    println(-1);
    return 0;
}
