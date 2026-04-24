#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); i++)
#define ll long long
#define all(v) (v).begin(), (v).end()

int arr[1000][1000];
int cnt[1000][1000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
    int n, m;
    cin >> n >> m;
    rep(i,n) rep(j,m) cin >> arr[i][j];
    rep(i,n) {
        int mx = arr[i][0], mxj = 0;
        rep(j,m) {
            if(arr[i][j] > mx) {
                mx = arr[i][j];
                mxj = j;
            }
        }
        cnt[i][mxj]++;
    }

    rep(j,m) {
        int mx = arr[0][j], mxi = 0;
        rep(i,n) {
            if(arr[i][j] > mx) {
                mx = arr[i][j];
                mxi = i;
            }
        }
        cnt[mxi][j]++;
    }
    ll ans = 0;
    rep(i,n) rep(j,m) {
        if(!cnt[i][j]) {
            ans += arr[i][j];
        }

    }
    cout << ans;
}
