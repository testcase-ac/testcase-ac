#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(5, 10);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int type = rnd.next(1, 3);
        int n = rnd.next(2, 10);
        vector<int> a(n);
        int p;
        if (type == 1) {
            // Impossible: total capacity < p
            int sum = 0;
            for (int i = 0; i < n; i++) {
                a[i] = rnd.next(1, 10);
                sum += a[i];
            }
            p = sum + rnd.next(1, 5);
        } else if (type == 2) {
            // Exact division
            int M = rnd.next(1, 10);
            p = M * n;
            for (int i = 0; i < n; i++) {
                a[i] = M + rnd.next(0, 10);
            }
        } else {
            // General case
            p = rnd.next(n, 20 * n);
            for (int i = 0; i < n; i++) {
                a[i] = rnd.next(1, 20);
            }
            int sum = accumulate(a.begin(), a.end(), 0);
            if (sum < p) {
                a[0] += p - sum;
            }
        }
        shuffle(a.begin(), a.end());
        println(p, n);
        println(a);
    }
    return 0;
}
