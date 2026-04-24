#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll arr[1000000], coming[1000000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		for(int i=0; i<n; i++) {
			cin >> arr[i];
		}
		coming[n-1] = -1;
		ll ans = 0;
		for(int i=n-2; i>=0; i--) {
			coming[i] = max(coming[i+1], arr[i+1]);
		}
		for(int i=0; i<n; i++) {
			if(arr[i] < coming[i])
				ans += coming[i] - arr[i];
		}
		cout << ans << '\n';
	}
}
