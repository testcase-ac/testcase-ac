#include <bits/stdc++.h>
using namespace std;
int arr[501], inv[501], ninv[501];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n;
		for(int i=1; i<=n; i++) {
			cin >> arr[i];
			inv[arr[i]] = i;
		}
		memcpy(ninv, inv, sizeof inv);
		cin >> m;
		while(m--) {
			int a, b;
			cin >> a >> b;
			if(inv[a] < inv[b]) {
				ninv[a]++;
				ninv[b]--;
			} else {
				ninv[a]--;
				ninv[b]++;
			}
		}
		sort(arr+1, arr+n+1, [&](int i, int j){return ninv[i] < ninv[j];});
		bool ok = 1;
		for(int i=1; i<=n; i++) {
			if(ninv[arr[i]] != i) {
				ok = 0;
				cout << "IMPOSSIBLE\n";
				break;
			}
		}
		if(ok) {
			for(int i=1; i<=n; i++)
				cout << arr[i] << ' ';
			cout << '\n';
		}
	}
}
