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
		int n;
		cin >> n;
		vector<pair<int,string>> arr(n);
		rep(i,n) cin >> arr[i].second >> arr[i].first;
		sort(arr.begin(), arr.end());
		cout << arr.back().second << '\n';
	}
}
