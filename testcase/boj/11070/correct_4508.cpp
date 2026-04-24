#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		int S[n] = {}, A[n] = {};
		for(int i=0; i<m; i++) {
			int a, b, p, q;
			cin >> a >> b >> p >> q;
			a--, b--;
			S[a] += p, S[b] += q, A[a] += q, A[b] += p;
		}
		vector<int> ans;
		for(int i=0; i<n; i++) {
			int v = S[i]*S[i] + A[i]*A[i];
			if(!v) {
				ans.push_back(0);
				continue;
			}
			int t = (int)((double)(S[i]*S[i])/(v)*1000);
			ans.push_back(t);
		}
		sort(ans.begin(), ans.end());
		cout << ans.back() << '\n' << ans[0] << '\n';
	}
}
