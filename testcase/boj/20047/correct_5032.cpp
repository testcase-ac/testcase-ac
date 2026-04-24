#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	string a, b;
	cin >> a >> b;
	int x, y;
	cin >> x >> y;
	char cx = a[x], cy = a[y];
	a.erase(a.begin()+y);
	a.erase(a.begin()+x);
	for(int i=0; i<=n-2; i++) {
		string c = a;
		c.insert(c.begin()+i, cx);
		bool ok = 1;
		for(int j=0; j<=i; j++) {
			if(b[j] != c[j]) {
				ok = 0;
				break;
			}
		}
		if(!ok)
			continue;
		bool used = 0;
		for(int j=i+1; j<=n-1; j++) {
			if(b[j] != c[j]) {
				if(!used) {
					if(b[j] == cy) {
						c.insert(c.begin()+j, cy);
						used = 1;
					} else {
						ok = 0;
						break;
					}
				} else {
					ok = 0;
					break;
				}
			}
		}
		if(ok) {
			return !(cout << "YES");
		}
	}
	cout << "NO";
}
