#include <bits/stdc++.h>
using namespace std;
#define int long long
map<string, string> counter = {{"Whiteking", "Blackking"}, {"Blackking", "Whiteking"}};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int acc = 0;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		acc ^= (t-2);
	}
	string a;
	cin >> a;
	if(acc) {
		cout << a;
	} else {
		cout << counter[a];
	}
}
