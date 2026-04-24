#include <bits/stdc++.h>
using namespace std;
int f(int n, int t) {
	int cnt = 0;
	while(n) {
		cnt += n/t;
		n /= t;
	}
	return cnt;
} 
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		cout << min(f(n, 2), f(n, 5)) << '\n';
	}
}
