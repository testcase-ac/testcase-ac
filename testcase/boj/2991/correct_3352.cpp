#include <bits/stdc++.h>
using namespace std;

const int MX = 1000;
int cnt[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	for(int i=0; i<MX; i++) {
		if(i%(a+b) < a) cnt[i]++;
		if(i%(c+d) < c) cnt[i]++;
	}
	for(int i=0; i<3; i++) {
		int t;
		cin >> t;
		cout << cnt[t-1] << '\n';
	}
}
