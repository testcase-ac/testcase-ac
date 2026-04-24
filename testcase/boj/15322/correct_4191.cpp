#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		int a, b;
		cin >> a >> b;
		int m = min(a,b);
		cout << (m-1)*2 << '\n';
	}
}
