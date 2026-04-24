#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: total amount T
    int T = rnd.next(1, 50);

    // Hyper-parameter: number of coin types k
    int k = rnd.next(1, min(6, T));

    // Hyper-parameter: bias towards small coin denominations
    bool smallValues = rnd.next(0, 1);
    vector<int> pool;
    if (smallValues && T >= 2) {
        int cut = max(1, T / 2);
        for (int i = 1; i <= cut; ++i) pool.push_back(i);
    } else {
        for (int i = 1; i <= T; ++i) pool.push_back(i);
    }
    // If pool too small, refill full range
    if ((int)pool.size() < k) {
        pool.clear();
        for (int i = 1; i <= T; ++i) pool.push_back(i);
    }
    shuffle(pool.begin(), pool.end());
    vector<int> ps(pool.begin(), pool.begin() + k);
    sort(ps.begin(), ps.end());

    // Output
    println(T);
    println(k);
    for (int p : ps) {
        // Hyper-parameter: some counts large, some small
        bool largeCnt = rnd.next(0, 1);
        int cnt;
        if (largeCnt) {
            cnt = rnd.next(20, 100);  // larger counts up to 100
        } else {
            cnt = rnd.next(1, 20);    // small counts up to 20
        }
        println(p, cnt);
    }

    return 0;
}
