#include <bits/stdc++.h>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define deb(v) cout << #v << ':' << v << '\n';
#define ldb long double
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;

	vector<string> arr1(n), arr2(n);
	rep(i,n) cin >> arr1[i];
	rep(i,n) cin >> arr2[i];
	bool arr[n][m];
	rep(i,n) rep(j,m) arr[i][j] = (arr1[i][j] == arr2[i][j]);
	if(n <= 2 || m <= 2) {
		rep(i,n) {
			rep(j,m) {
				if(!arr[i][j])
					return !(cout << -1);
			}
		}
		return !(cout << 0);
	}
	int cnt = 0;
	rep(i,n-2) {
		rep(j,m-2) {
			if(!arr[i][j]) {
				rep(di,3) {
					rep(dj,3) {
						arr[i+di][j+dj] = !arr[i+di][j+dj];
					}
				}
				cnt++;
			}
		}
	}
	rep(i,n) {
		rep(j,m) {
			if(!arr[i][j])
				return !(cout << -1);
		}
	}
	cout << cnt;
}
