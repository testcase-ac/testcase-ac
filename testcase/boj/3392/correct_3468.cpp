#include <bits/stdc++.h>
using namespace std;
const int MX = 10003, MXY = 30003;
int segt[MXY*4], cnt[MXY*4];
void update(int i, int ln, int rn, int l, int r, int v) {
	if(r < ln || l > rn || l > r) return;
	if(l == ln && r == rn) {
		segt[i] += v;
	} else {
		int m = (ln+rn)/2;
		update(i*2, ln, m, l, min(r, m), v);
		update(i*2+1, m+1, rn, max(l, m+1), r, v);
	}
	cnt[i] = (segt[i] ? rn-ln+1 : (rn == ln ? 0 : cnt[i*2]+cnt[i*2+1]));
}
struct Rec {
	int y1, y2, v;
};
vector<Rec> bucket[MXY];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		bucket[x1].push_back({y1,y2,1});
		bucket[x2].push_back({y1,y2,-1});
	}
	int ans = 0;
	for(int i=0; i<MXY; i++) {
		for(Rec r: bucket[i]) {
			update(1, 0, MXY, r.y1, r.y2-1, r.v);
		}
		ans += cnt[1];
	}
	cout << ans;
}
