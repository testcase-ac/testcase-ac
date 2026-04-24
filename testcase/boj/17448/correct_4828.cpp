#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> pos, neg, posm, negm;
const int MOD = 1e9+7;
int ans = 1;
int last2(vector<int>& v) {
	if(v.size() == 1)
		return v.back();
	return v.back() * v[v.size()-2];
}
void pop(vector<int>& v) {
	ans = (ans * v.back()) % MOD;
	v.pop_back();
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		if(t > 1)
			pos.push_back(t);
		else if(t < -1)
			neg.push_back(-t);
	}
	sort(pos.begin(), pos.end());
	sort(neg.begin(), neg.end());
	while(k && (pos.size() || neg.size())) {
		if(k == 1) {
			if(neg.size()) {
				pop(neg);
				k--;
			}
			break;
		}
		// k >= 2
		if(!pos.size()) {
			pop(neg);
			k--;
			continue;
		}
		if(!neg.size()) {
			pop(pos);
			if(pos.size())
				pop(pos);
			k -= 2;
			continue;
		}
		// // pos.size() && neg.size()
		// if(pos.size() == 1) {
		// 	if(pos.back() > last2(neg)) {
		// 		pop(pos);
		// 		k -= 2;
		// 	} else {
		// 		pop(neg);
		// 		if(neg.size())
		// 			pop(neg);
		// 		k -= 2;
		// 	}
		// 	continue;
		// }
		// // pos.size() >= 2 && neg.size()
		if(last2(pos) > last2(neg)) {
			pop(pos);
			if(pos.size())
				pop(pos);
			k -= 2;
		} else {
			pop(neg);
			k--;
		}
	}
	cout << ans;
}
