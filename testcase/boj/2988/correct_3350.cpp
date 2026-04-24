#include <bits/stdc++.h>
using namespace std;
const int MX = 100002;
int arr[3][MX], cnt[3][MX];
bool delnum[MX], delcol[MX];
vector<pair<int, int>> where[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<3; i++) {
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
			cnt[i][arr[i][j]]++;
			where[arr[i][j]].push_back({i, j});
		}
	}
	int ans = 0;
	queue<int> delque;
	for(int i=0; i<3; i++) {
		for(int j=1; j<=n; j++) {
			if(!cnt[i][j] && !delnum[j]) {
				delque.push(j);
				delnum[j] = 1;
			}
		}
	}
	while(!delque.empty()) {
		ans++;
		int d = delque.front();
		delque.pop();
		for(auto pr: where[d]) {
			int r, c;
			tie(r, c) = pr;
			if(!delcol[c]) {
				delcol[c] = 1;
				for(int i=0; i<3; i++) {
					cnt[i][arr[i][c]]--;
					if(!cnt[i][arr[i][c]] && !delnum[arr[i][c]]) {
						delnum[arr[i][c]] = 1;
						delque.push(arr[i][c]);
					}
				}
			}
		}
	}
	cout << ans;
}
