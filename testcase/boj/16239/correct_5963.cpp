#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int k, n;
	cin >> k >> n;
	for(int i=1; i<n; i++) {
		cout << i << '\n';
		k -= i;
	}
	cout << k;
}
