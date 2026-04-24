#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		int arr[n][m];
		rep(i,n)rep(j,m) cin >> arr[i][j];
		int ans = 0;
		rep(j,m) {
			int nextput = n-1;
			for(int ptr=n-1; ptr>=0; ptr--) {
				if(arr[ptr][j]) {
					ans += nextput - ptr;
					nextput--;
				}
			}
		}
		cout << ans << '\n';
	}
}
