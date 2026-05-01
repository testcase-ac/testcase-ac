#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 4);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        vector<int> coef = { -1, 0, 1 };
        int tcoef = rnd.any(coef);
        int K = rnd.wnext(13, tcoef) + 3;
        K = max(3, min(K, 15));
        println(K);
        vector<int> a(K);
        int pat = rnd.next(0, 2);
        if (pat == 0) {
            // completely random sizes
            for (int i = 0; i < K; i++)
                a[i] = rnd.next(1, 100);
        } else if (pat == 1) {
            // increasing sequence
            int cur = rnd.next(1, 10);
            for (int i = 0; i < K; i++) {
                cur += rnd.next(0, 10);
                a[i] = cur;
            }
        } else {
            // few distinct values
            int d = rnd.next(2, min(5, K));
            vector<int> vals(d);
            for (int i = 0; i < d; i++)
                vals[i] = rnd.next(1, 100);
            for (int i = 0; i < K; i++)
                a[i] = rnd.any(vals);
            shuffle(a.begin(), a.end());
        }
        println(a);
    }
    return 0;
}
