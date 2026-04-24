#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, t;
	cin >> n >> t;
	for(int i=1; i<=n; i++) {
		int v;
		cin >> v;
		if(t-v<0) return !(cout << i-1);
		t -= v;
	}
	cout << n;
}
