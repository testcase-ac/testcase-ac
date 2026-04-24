#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, w1 = 0, w2 = 0, d = 0, t = 0;
		cin >> n;
		string a, b;
		cin >> a >> b;
		for(int i=0; i<n; i++) {
			if(a[i] == 'W') w1++;
			if(b[i] == 'W') w2++;
			if(a[i] != b[i]) t++;
		}
		d = abs(w1-w2);
		cout << d+(t-d)/2 << '\n';
	}
}
