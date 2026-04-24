#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char arr[20][21];
ll acc[1<<20], tim[1<<20];
int t = 2, cur[20], nxt[20], n, bm, sum;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	int cbm = 0;
	ll csum = 0;
	for(int j=0; j<n; j++) {
		if(arr[0][j] == '1') {
			cur[j] = 1;
			cbm |= (1<<j);
			csum++;
		}
	}
	acc[cbm] = csum;
	tim[cbm] = 1;
	while(t <= m) {
		bm = 0, sum = 0;
		memset(nxt, 0, sizeof nxt);
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(arr[i][j] == '1')
					nxt[j] += cur[i]&1 ? 1 : 2;
			}
		}
		for(int i=0; i<n; i++) {
			if(nxt[i]&1) bm |= (1<<i);
			sum += nxt[i];
		}
		if(tim[bm]) {
			ll tdiff = t-tim[bm], sdiff = acc[cbm] - acc[bm] + sum;
			int rm = m-t+1;
			csum += sdiff*(rm/tdiff);
			t += (rm/tdiff)*tdiff;
			memset(tim, 0, sizeof tim);
		} else {
			csum += sum;
			acc[bm] = csum;
			tim[bm] = t;
			cbm = bm;
			memcpy(cur, nxt, sizeof cur);
			t++;
		}
	}
	cout << csum;
}
