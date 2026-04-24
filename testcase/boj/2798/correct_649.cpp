#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	int arr[n];
	rep(i,n) cin >> arr[i];
	int ans = 0;
	rep(i,n) rep(j,n) rep(k,n) {
		if(i == j || j == k || i == k) continue;
		int s = arr[i]+arr[j]+arr[k];
		if(s <= m && s > ans)
			ans = s;
	}
	cout << ans;
}
