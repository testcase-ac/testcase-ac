#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, t, c, p;
	cin >> n >> t >> c >> p;
	cout << (n-1)/t*c*p;
}
