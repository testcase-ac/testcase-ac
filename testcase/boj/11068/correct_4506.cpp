#include <bits/stdc++.h>
using namespace std;

bool check(int n, int base) {
	vector<int> v;
	while(n) {
		v.push_back(n%base);
		n /= base;
	}
	int l = (int)v.size();
	for(int i=0; i<l/2; i++) {
		if(v[i] != v[l-1-i]) return false;
	}
	return true;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		bool ok = false;
		for(int i=2; i<=64; i++) {
			if(check(n, i)) {
				ok = true;
				break;
			}
		}
		cout << ok << '\n';
	}
}
