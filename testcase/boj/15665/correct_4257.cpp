#include <bits/stdc++.h>
using namespace std;
vector<int> v, o;
int n, m;
void f(int p) {
	if(p == m) {
		for(int i: o)
			cout << i << ' ';
		cout << '\n';
		return;
	}
	for(int i: v) {
		o.push_back(i);
		f(p+1);
		o.pop_back();
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	set<int> s;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		s.insert(t);
	}
	v = vector<int>(s.begin(), s.end());
	f(0);
}
