#include <bits/stdc++.h>
using namespace std;

struct Pt {
	int t, r, c;
};
Pt pos[100], me;
int R, C;
int dist(Pt a, Pt b) {
	return abs(a.r-b.r)+abs(a.c-b.c);
}
Pt f(int a, int b) {
	int r, c;
	if(a <= 2) {
		r = (a == 1 ? R : 0);
		c = b;
	} else {
		r = R-b;
		c = (a == 3 ? 0 : C);
	}
	return {a, r, c};
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, a, b;
	cin >> C >> R >> n;
	for(int i=0; i<n; i++) {
		cin >> a >> b;
		pos[i] = f(a,b);
	}
	cin >> a >> b;
	me = f(a,b);
	int ans = 0;
	for(int i=0; i<n; i++) {
		Pt p = pos[i];
		int s = p.t+me.t, d = dist(p, me);
		if(s == 3) {
			ans += d+min({p.c, C-p.c, me.c, C-me.c})*2;
		} else if(s == 7) {
			ans += d+min({p.r, R-p.r, me.r, R-me.r})*2;
		} else {
			ans += d;
		}
	}
	cout << ans;
}
