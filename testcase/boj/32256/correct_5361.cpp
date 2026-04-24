#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        int ub = (N+1)/2;
        if(N <= 4) {
            cout << ub << '\n';
            continue;
        }
        int len = 64 - __builtin_clzll(N), 
            diff = 0, 
            endidx = 1ll << len, 
            mxdiff = ((len - 4 >= 0) ? 1ll << (len - 4) : 0);
        for(int i=len-1; i; i--) {
            if(N & (1ll << (i-1))) {
                int dist = endidx - N;
                if(dist <= (mxdiff-1) * 2) {
                    diff = (dist + 1) / 2;
                } else if(dist == mxdiff * 2 - 1) {
                    diff = mxdiff;
                } else {
                    diff = max(0ll, mxdiff - (dist - mxdiff * 2 + 2) / 2);
                }
                break;
            } else {
                endidx -= 1ll << (i-1);
                mxdiff /= 2;
            }
        }
        diff = max(0ll, diff);
        //printf("at N = %lld, len = %lld, endidx = %lld, diff = %lld\n", N, len, endidx, diff);
        cout << ub - diff << '\n';
    }
}
