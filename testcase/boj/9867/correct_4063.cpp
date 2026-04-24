#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifdef ONLINE_JUDGE
const int MX = 1<<16;
#else
const int MX = 8;
#endif
int seg[MX*2][4];
void build(int i) {
	int *lft = seg[i*2], *rht = seg[i*2+1], *cur = seg[i];
	cur[0] = max(lft[1]+rht[0], lft[0]+rht[2]);
	cur[1] = max(lft[1]+rht[1], lft[0]+rht[3]);
	cur[2] = max(lft[2]+rht[2], lft[3]+rht[0]);
	cur[3] = max(lft[2]+rht[3], lft[3]+rht[1]);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, d;
	cin >> n >> d;
	for(int i=MX; i<MX+n; i++)
		cin >> seg[i][0];
	for(int i=MX-1; i; i--)
		build(i);
	int ans = 0;
	while(d--) {
		int a, b;
		cin >> a >> b;
		a--;
		a += MX;
		seg[a][0] = b;
		while(a /= 2)
			build(a);
		ans += seg[1][0];
	}
	cout << ans;
}
