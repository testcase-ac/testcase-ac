#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=2; i*i<=n; i++) {
		if(n % i == 0) {
			int t = n / i;
			return !(cout << (n-t));
		}
	}
	cout << n-1;
}
