#include <bits/stdc++.h>
using namespace std;
const int BUK = 320;
typedef long long ll;
ll num[BUK][BUK], add[BUK][BUK], step[BUK][BUK];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> num[i/BUK][i%BUK];
	}
	int q;
	cin >> q;
	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int l, r;
			cin >> l >> r;
			int st = l/BUK, ed = r/BUK, cur = 1;
			add[l/BUK][l%BUK]++;
			step[l/BUK][l%BUK]++;
			while(++st <= ed) {
				add[st][0] += st*BUK-l+1;
				step[st][0]++;
			}
			if(r % BUK == BUK-1) continue;
			r++;
			add[r/BUK][r%BUK] -= r-l+1;
			step[r/BUK][r%BUK]--;
		} else {
			int x, b;
			cin >> x;
			b = x/BUK;
			ll adding = 0, steping = 0;
			for(int i=0; i<BUK; i++) {
				adding += steping;
				adding += add[b][i];
				steping += step[b][i];
				add[b][i] = 0;
				step[b][i] = 0;
				num[b][i] += adding;
			}
			cout << num[x/BUK][x%BUK] << '\n';
		}
	}
}
