#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	int ans = 0;
	while(n) {
		int l = 1, r = 1e5;
		while(l < r) {
			int m = (l+r+1)/2;
			if((long long)(m+1)*m/2 <= n) {
				l = m;
			} else {
				r = m-1;
			}
		}
		ans += l;
		n -= (l+1)*l/2;
	}
	cout << ans;
}
