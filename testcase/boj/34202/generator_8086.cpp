#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small N for readability
    int N = rnd.next(2, 12);
    // Prepare middle nodes 2..N-1
    vector<int> mids;
    for (int i = 2; i <= N - 1; ++i)
        mids.push_back(i);
    vector<int> mid;
    // Select pattern based on N
    if (N >= 4) {
        int type = rnd.next(0, 3);
        if (type == 0) {
            // Simple path
            mid = mids;
        } else if (type == 1) {
            // Random permutation
            mid = mids;
            shuffle(mid.begin(), mid.end());
        } else if (type == 2) {
            // Zigzag from ends
            int l = 0, r = (int)mids.size() - 1;
            while (l <= r) {
                mid.push_back(mids[l++]);
                if (l <= r) mid.push_back(mids[r--]);
            }
        } else {
            // Mountain shape: increasing then decreasing
            int m = mids.size();
            int len_inc = rnd.next(1, m - 1);
            // increasing part: 2 .. 2+len_inc-1
            for (int v = 2; v <= 2 + len_inc - 1; ++v)
                mid.push_back(v);
            // decreasing part: N-1 .. 2+len_inc
            for (int v = N - 1; v >= 2 + len_inc; --v)
                mid.push_back(v);
        }
    } else {
        // For very small N, just use the trivial middle
        mid = mids;
    }
    // Build the visit order p: p1=1, then mids, then pN=N
    vector<int> p;
    p.push_back(1);
    for (int x : mid) p.push_back(x);
    p.push_back(N);
    // Compute traversal counts c_i
    vector<long long> c(N - 1, 0);
    for (int i = 0; i + 1 < (int)p.size(); ++i) {
        int u = p[i], v = p[i + 1];
        int lo = min(u, v), hi = max(u, v);
        for (int e = lo; e < hi; ++e) {
            // edge between e and e+1 is index e-1 in c
            c[e - 1]++;
        }
    }
    // Output
    println(N);
    println(c);
    return 0;
}
