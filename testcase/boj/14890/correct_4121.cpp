#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, l;
	cin >> n >> l;
	int arr[n][n];
	rep(i,n)rep(j,n) cin >> arr[i][j];
	int ans = 0;
	rep(i,n) {
		int now = arr[i][0], cnt = 1, j;
		for(j=1; j<n; j++) {
			if(arr[i][j] == now)
				cnt++;
			else {
				bool builded = false;
				if(abs(arr[i][j] - now) > 1) {
					break;
				} else if(arr[i][j] == now + 1) {
					if(cnt < l) break;
				} else if(arr[i][j] == now - 1) {
					bool dobreak = false;
					rep(k, l)
						if(j+k>=n || arr[i][j+k] != arr[i][j]) {
							dobreak = true;
							break;
						}
					if(dobreak) break;
					builded = true;
				}
				now = arr[i][j];
				cnt = (builded ? 1-l:1);
			}
		}
		if(j == n) {
			ans++;
		}
	}
	rep(i,n) {
		int now = arr[0][i], cnt = 1, j;
		for(j=1; j<n; j++) {
			if(arr[j][i] == now)
				cnt++;
			else {
				bool builded = false;
				if(abs(arr[j][i] - now) > 1) {
					break;
				} else if(arr[j][i] == now + 1) {
					if(cnt < l) break;
				} else if(arr[j][i] == now - 1) {
					bool dobreak = false;
					rep(k, l)
						if(j+k>=n || arr[j+k][i] != arr[j][i]) {
							dobreak = true;
							break;
						}
					if(dobreak) break;
					builded = true;
				}
				now = arr[j][i];
				cnt = (builded ? 1-l : 1);
			}
		}
		if(j == n)  {
			ans++;
		}
	}
	cout << ans;
}
