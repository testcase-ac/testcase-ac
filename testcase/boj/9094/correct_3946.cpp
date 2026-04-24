#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, m, ans = 0;
		cin >> n >> m;
		for(int i=1; i<n; i++) {
			for(int j=i+1; j<n; j++) {
				if((i*i+j*j+m)%(i*j) == 0)
					ans++;
			}
		}
		cout << ans << '\n';
	}
}
