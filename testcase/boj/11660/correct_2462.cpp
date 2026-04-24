#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int arr[1025][1025], sum[1025][1025];

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) cin >> arr[i][j];
	for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) sum[i][j] = -sum[i-1][j-1] + arr[i][j] + sum[i-1][j] + sum[i][j-1];
	while(m--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		cout << sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1] << '\n';
	}

}
