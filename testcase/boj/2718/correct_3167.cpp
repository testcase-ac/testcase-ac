#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	vector<ll> ans = {0,1,5}, exact = {0,1,4};
	while(ans.back() < INT_MAX) {
		int i = ans.size();
		ll nxt = (i&1 ? 2 : 3);
		exact.push_back(nxt);
		for(int j=1; j<i; j++) {
			nxt += (ans[j]*exact[i-j]);
		}
		ans.push_back(nxt);
	}
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		cout << ans[n] << '\n';
	}
}
