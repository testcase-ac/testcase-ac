#include <bits/stdc++.h>
using namespace std;
#define int long long
int MOD = 1234567891, prime = 31, MXL = 1e6+2;
int charh(char c) {
    return c-'a'+1;
}
vector<int> po;
struct hasher {
	int n;
	vector<int> po, acc;
	hasher(string &s) {
		n = s.size();
		acc.resize(n);
		if(po.empty()) {
			po.resize(MXL);
			po[0] = 1;
			for(int i=1; i<MXL; i++) {
				po[i] = (po[i-1] * prime) % MOD;
			}
		}
		acc[0] = charh(s[0]);
		for(int i=1; i<s.size(); i++) {
			acc[i] = (acc[i-1] + charh(s[i]) * po[i]) % MOD;
		}
	}
	int val(int l, int r) { // [l, r]
		int t = (r >= 0 ? acc[r] : 0) - (l ? acc[l-1] : 0);
		if(t < 0)
			t += MOD;
		return (t * po[MXL-1-r]) % MOD;
	}
};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int t=1;; t++) {
		int n;
		cin >> n;
		if(!n) break;
		string s;
		cin >> s;
		hasher hsh(s);
		cout << "Test case #" << t << '\n';
		vector<int> ans(n);
		for(int ln=1; ln<=n/2; ln++) {
			int h = hsh.val(0, ln-1);
			for(int i=1;; i++) {
				int l = ln*i, r = ln*(i+1)-1;
				if(r >= n) break;
				int tmp = hsh.val(l, r);
				if(tmp != h)
					break;
				if(!ans[r])
					ans[r] = i+1;
			}
		}
		for(int i=0; i<n; i++) {
			if(ans[i]) {
				cout << i+1 << ' ' << ans[i] << '\n';
			}
		}
		cout << '\n';
	}
}
