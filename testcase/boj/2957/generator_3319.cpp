#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small size
    int N = rnd.next(1, 10);

    // Choose generation style for diversity
    int style = rnd.next(0, 4);
    vector<int> a(N);
    // Base sorted array 1..N
    vector<int> base(N);
    iota(base.begin(), base.end(), 1);

    if (style == 0) {
        // Ascending
        a = base;
    } else if (style == 1) {
        // Descending
        a = base;
        reverse(a.begin(), a.end());
    } else if (style == 2) {
        // Pure random
        a = base;
        shuffle(a.begin(), a.end());
    } else if (style == 3) {
        // Low-High alternation: 1, N, 2, N-1, ...
        int l = 1, r = N, idx = 0;
        while (l <= r) {
            if (l == r) {
                a[idx++] = l;
                break;
            }
            a[idx++] = l++;
            a[idx++] = r--;
        }
    } else {
        // Median-recursive: balanced-like insertion order
        vector<int> seq;
        function<void(int,int)> dfs = [&](int l, int r) {
            if (l > r) return;
            int m = (l + r) / 2;
            seq.push_back(m);
            dfs(l, m - 1);
            dfs(m + 1, r);
        };
        dfs(1, N);
        a = seq;
    }

    // Output
    println(N);
    for (int x : a) {
        println(x);
    }
    return 0;
}
