#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, r, s, arr[18][18], cur[18][18], sum[18];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m >> r >> s;
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			cin >> arr[i][j];
		}
	}
	vector<int> p(n-1);
	for(int i=0; i<r; i++) {
		p[i] = 1;
	}
	int ans = LLONG_MAX;
	do {
		for(int j=0; j<m; j++) {
			int ti = 0, ts = 0;
			for(int i=0; i<n; i++) {
				ts += arr[i][j];
				cur[ti][j] = ts;
				if(i < n-1 && p[i]) {
					ts = 0;
					ti++;
				}
			}
		}
		int L = 0, R = 200000*18*18;
		while(L < R) {
			int M = (L+R)/2, part = 1;
			bool ok = 1;
			memset(sum, 0, sizeof sum); // error
			for(int j=0; j<m; j++) {
				bool tok = 1;
				for(int i=0; i<=r; i++) { // error
					if(cur[i][j] > M) {
						ok = 0;
						goto end;
					}
					if(sum[i] + cur[i][j] > M) {
						tok = 0;
					}
					sum[i] += cur[i][j];
				}
				if(!tok) {
					memset(sum, 0, sizeof sum);
					part++;
					j--;
				}
			}
			if(part > s+1) {
				ok = 0;
			}
			end:;
			if(ok) {
				R = M;
			} else {
				L = M+1;
			}
		}
		ans = min(ans, L);
	} while(prev_permutation(p.begin(), p.end()));
	cout << ans;
}
