#include <bits/stdc++.h>
using namespace std;
#define int long long
int W, N, A[500001];
bool ok[500001];
bool solve(int m) {
    int l = 0, r = 0, cnt = 0;
    ok[0] = 1;
    for(int i=1; i<=N; i++) {
        while(A[i] - A[r] >= m) {
            cnt += ok[r];
            r++;
        }
        while(A[i] - A[l] > W) {
            cnt -= ok[l];
            l++;
        }
        ok[i] = (l <= r && cnt > 0);
    }
    return ok[N];
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> W >> N;
    for(int i=1; i<=N; i++) {
        cin >> A[i];
        A[i] += A[i-1];
    }
    int l = 0, r = W;

    while(l < r) {
        int m = (l+r+1)/2;
        if(solve(m)) {
            l = m;
        } else {
            r = m-1;
        }
    }
    cout << (W-l)*(W-l) << '\n';
}
