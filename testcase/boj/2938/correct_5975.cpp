#include <bits/stdc++.h>
using namespace std;
vector<int> buk[3], ans;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		buk[t%3].push_back(t);
	}
	if((buk[1].size()+buk[2].size()+1 < buk[0].size()) || (buk[1].size() && buk[2].size() && buk[0].empty()))
		return !(cout << -1);
	int rm = (int)buk[0].size() - 1;
	for(int i: buk[1]) {
		if(rm > 0)
			cout << buk[0][rm--] << ' ';
		cout << i << ' ';
	}
	if(buk[0].size())
		cout << buk[0][0] << ' ';
	for(int i: buk[2]) {
		cout << i << ' ';
		if(rm > 0)
			cout << buk[0][rm--] << ' ';
	}
}
