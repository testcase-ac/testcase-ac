#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p, m, f, c;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	for(int i=0; i<T; i++) {
		cin >> p >> m >> f >> c;
		ll k = m/p*c, t = f-c;
		cout << (k < f ? 0 : (k-f+t)/t - k/f) << '\n';
	}

}
