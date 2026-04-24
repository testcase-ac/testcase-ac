#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, l, t = 0, p = 0;
	cin >> n >> l;
	for(int i=0; i<n; i++) {
		int d, r, g;
		cin >> d >> r >> g;
		t += (d-p);
		if(t%(r+g) < r)
			t += r - t%(r+g);
		p = d;
	}
	cout << t+(l-p);
}
