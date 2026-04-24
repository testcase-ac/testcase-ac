#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[6][3];
ll query[4];
int ans[4];
ll calc() {
	ll r = 0;
	for(int i=0; i<6; i++) {
		for(int j=0; j<3; j++) {
			r *= 7;
			r += a[i][j];
		}
	}
	return r;
}
void f(int i, int j, ll h) {
	int ni = i, nj = j+1;
	ll nh = h;
	if(j == i+1 && i) {
		for(int t=0; t<3; t++) {
			nh *= 7;
			nh += a[i-1][t];
		}
	}
	if(i == 5) {
		for(int t=0; t<3; t++) {
			h *= 7;
			h += a[4][t];
		}
		for(int t=0; t<3; t++) {
			h *= 7;
			h += a[5][t];
		}
		for(int k=0; k<4; k++) {
			if(h == query[k]) {
				ans[k] = 1; // break?
			}
		}
		return;
	}
	if(nj == 6) {
		ni++;
		nj = ni+1;
	}
	for(int k=0; k<3; k++) {
		a[i][k]++;
		a[j][2-k]++;
		f(ni, nj, nh);
		a[i][k]--;
		a[j][2-k]--;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T = 4;
	for(int t=0; t<T; t++) {
		for(int i=0; i<6; i++) {
			for(int j=0; j<3; j++) {
				cin >> a[i][j];
			}
		}
		query[t] = calc();
	}
	memset(a, 0, sizeof a);
	f(0, 1, 0);
	for(int i=0; i<4; i++) {
		cout << ans[i] << ' ';
	}
}
