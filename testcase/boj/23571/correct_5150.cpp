#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> A, B, cur, up, dn;
int last_ans, N;
bool solve(int lim) {
    int l = 0, r = N-1;
    while(l < N && cur[l] <= lim) {
        l++;
    }
    while(r >= 0 && cur[r] <= lim) {
        r--;
    }
    if(l > r) { // all in cur is better than lim
        last_ans = A[0];
        return 1;
    }
    if(l == r) {
        last_ans = A[l];
        return 1;
    }
    // l < r
    int dnl = r;
    while(dnl >= 0 && dn[dnl] <= lim) {
        dnl--;
    }
    // printf("dnl = %lld, l = %lld, \n", dnl, l);
    if(dnl <= l) {
        last_ans = A[dnl];
        return 1;
    }
    int cnt = 0, pos;
    for(int i=l; i<=r; i++) {
        if(cur[i] > lim) {
            pos = i;
            cnt++;
        }
    }
    if(cnt == 1) {
        last_ans = A[pos];
        return 1;
    }
    bool ok = 1;
    for(int i=l; i<r; i++) {
        if(up[i] > lim) {
            ok = 0;
            break;
        }
    }
    if(ok) {
        last_ans = A[r];
        return 1;
    }

    last_ans = -1;
    return 0;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    A = B = cur = up = dn = vector<int>(N);
    for(int i=0; i<N; i++) {
        cin >> A[i];
    }
    for(int i=0; i<N; i++) {
        cin >> B[i];
    }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    for(int i=0; i<N; i++) {
        cur[i] = abs(A[i] - B[i]);
    }
    dn[0] = INT_MAX;
    for(int i=1; i<N; i++) {
        dn[i] = abs(A[i] - B[i-1]);
    }
    up[N-1] = INT_MAX;
    for(int i=0; i<N-1; i++) {
        up[i] = abs(A[i] - B[i+1]);
    }
    int l = 0, r = 1e9;
    while(l < r) {
        int m = (l + r) / 2;
        if(solve(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    solve(l);
    // printf("l = %lld\n", l);
    assert(last_ans != -1);
    cout << last_ans;
}
