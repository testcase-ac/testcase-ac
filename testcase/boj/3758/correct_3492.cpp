#include <bits/stdc++.h>
using namespace std;
int record[100][100], cnt[100], lastt[100];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, k, t, m;
		cin >> n >> k >> t >> m;
		t--;
		memset(record, 0, sizeof record);
		memset(cnt, 0, sizeof cnt);
		memset(lastt, 0, sizeof lastt);
		for(int i=0; i<m; i++) {
			int id, p, s;
			cin >> id >> p >> s;
			id--, p--;
			record[id][p] = max(record[id][p], s);
			cnt[id]++;
			lastt[id] = i;
		}
		int mypt = accumulate(record[t], record[t]+k, 0), ans = 1;
		for(int i=0; i<n; i++) {
			int pt = accumulate(record[i], record[i]+k, 0);
			if(pt > mypt)
				ans++;
			else if(pt == mypt) {
				if(cnt[i] < cnt[t])
					ans++;
				else if(cnt[i] == cnt[t]) {
					if(lastt[i] < lastt[t])
						ans++;
				}
			}
		}
		cout << ans << '\n';
	}
}
