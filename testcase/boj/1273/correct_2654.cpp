#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 3e5+2, MXT = 1<<22;
int arr[3][MX], seg[MXT*2];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> v[3];
	for(int i=0; i<3; i++) {
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
		}
	}
	for(int i=0; i<n; i++) {
		v[0].push_back(arr[0][i]);
		v[1].push_back(arr[0][i] + arr[1][i]);
		v[2].push_back(arr[0][i] + arr[1][i] + arr[2][i]);
	}
	for(int i=0; i<3; i++) {
		sort(v[i].begin(), v[i].end());
	}
	for(int i=0; i<MXT; i++) {
		seg[i+MXT] = 1;
	}
	for(int i=MXT-1; i; i--) {
		seg[i] = seg[i*2] + seg[i*2+1];
	}
	int q;
	cin >> q;
	while(q--) {
		int val;
		cin >> val;
		if(val >= MXT) {
			cout << "0\n";
			continue;
		}
		int p = 1;
		while(p < MXT) {
			if(val < seg[p*2]) {
				p *= 2;
			} else {
				val -= seg[p*2];
				p = p*2+1;
			}
		}
		assert(seg[p]);
		seg[p] = 0;
		int t = p;
		while(t /= 2) {
			seg[t] = seg[t*2] + seg[t*2+1];
		}
		p -= MXT;
		//printf("real p is %d\n", p);
		int cnt[3] = {0, };
		for(int i=0; i<3; i++) {
			cnt[i] = v[i].end() - lower_bound(v[i].begin(), v[i].end(), p);
			//printf("cnt %d = %d | ", i, cnt[i]);
		}
		cnt[1] -= cnt[0];
		cnt[2] -= cnt[1] + cnt[0];
		//printf("\n");
		cout << cnt[0] + cnt[1]*2 + cnt[2]*5 << '\n';
	}
}
