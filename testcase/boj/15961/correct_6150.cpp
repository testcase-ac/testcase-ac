#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, d, k, c;
	cin >> n >> d >> k >> c;
	int arr[2*n];
	int kinds[d+1] = {}, cnt = 0;
	rep(i,n){
		cin >> arr[i];
		arr[n+i] = arr[i];
	}
	rep(i,k) {
		if(!kinds[arr[i]]) cnt++;
		kinds[arr[i]]++;
	}
	int ans = 0;
	for(int i=k; i<n+k; i++) {
		if(!kinds[arr[i]]) cnt++;
		kinds[arr[i]]++;
		kinds[arr[i-k]]--;
		if(!kinds[arr[i-k]]) cnt--;
		ans = max(ans, cnt+(!kinds[c]));
	}
	cout << ans;
}
