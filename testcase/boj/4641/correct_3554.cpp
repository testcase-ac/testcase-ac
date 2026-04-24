#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
		bool arr[300] = {};
		int t;
		cin >> t;
		if(t == -1) return 0;
		while(t) {
			arr[t] = 1;
			cin >> t;
		}
		int ans = 0;
		for(int i=1; i<=50; i++) {
			if(arr[i] && arr[2*i])
				ans++;
		}
		cout << ans << '\n';
	}
}
