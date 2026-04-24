#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	set<int> s;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		vector<int> v = {t};
		for(int k: s) {
			v.push_back(t+k);
			v.push_back(abs(t-k));
		}
		for(int k: v)
			s.insert(k);
	}
	int m;
	cin >> m;
	while(m--) {
		int t;
		cin >> t;
		cout << (s.find(t) != s.end() ? 'Y' : 'N') << ' ';
	}
}
