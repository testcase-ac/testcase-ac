#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		int csum = 0, msum = INT_MIN;
		for(int i=0; i<n; i++) {
			int t;
			cin >> t;
			csum += t;
			msum = max(csum, msum);
			csum = max(0, csum);
		}
		cout << msum << '\n';
	}
}
