#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int len, n;
		cin >> len >> n;
		int a[n];
		for(int i=0; i<n; i++) {
			cin >> a[i];
		}
		int minans = 0, maxans = 0;
		for(int i=0; i<n; i++) {
			minans = max(minans, min(a[i], len-a[i]));
			maxans = max({maxans, a[i], len-a[i]});
		}
		cout << minans << ' ' << maxans << '\n';
	}
}
