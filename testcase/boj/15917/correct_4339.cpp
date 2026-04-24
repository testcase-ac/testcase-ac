#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		int t;
		cin >> t;
		cout << (__builtin_popcount(t) == 1) << '\n';
	}
}
