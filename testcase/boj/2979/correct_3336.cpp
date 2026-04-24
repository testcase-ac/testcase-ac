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
	int cost[4];
	cin >> cost[1] >> cost[2] >> cost[3];
	cost[0] = 0;
	pair<int, int> arr[3];
	rep(i,3) cin >> arr[i].first >> arr[i].second;
	int ans = 0;
	for(int i=1; i<=100; i++) {
		int cnt = 0;
		rep(j,3) if(arr[j].first <= i && i < arr[j].second) cnt++;
		ans += cost[cnt]*cnt;
	}
	cout << ans;
}
