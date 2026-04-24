#include <bits/stdc++.h>
using namespace std;

char arr[500][501];
bool seen[500][500];
vector<pair<int, int>> wood;
pair<int, int> init, fin;
int di[] = {1,-1,0,0}, dj[] = {0,0,1,-1}, R, C;
bool valid(int i, int j) {
	return 0 <= i && i < R && 0 <= j && j < C && !seen[i][j];
}
bool ok(int dist) {
	memset(seen, 0, sizeof seen);
	queue<pair<int, int>> que;
	if(dist) {
		for(auto pr: wood) {
			que.push(pr);
			seen[pr.first][pr.second] = 1;
		}
		while(--dist) {
			int s = que.size();
			while(s--) {
				int i, j;
				tie(i,j) = que.front();
				que.pop();
				for(int t=0; t<4; t++) {
					int ti = i+di[t], tj = j+dj[t];
					if(valid(ti, tj)) {
						seen[ti][tj] = 1;
						que.push({ti, tj});
						auto pr = make_pair(ti, tj);
						if(pr == init || pr == fin)
							return 0;
					}
				}
			}
		}
	}
	que = queue<pair<int, int>>();
	que.push(init);
	while(!que.empty()) {
		int i, j;
		tie(i,j) = que.front();
		if(que.front() == fin) return 1;
		que.pop();
		for(int t=0; t<4; t++) {
			int ti = i+di[t], tj = j+dj[t];
			if(valid(ti, tj)) {
				seen[ti][tj] = 1;
				que.push({ti, tj});
				if(make_pair(ti, tj) == fin)
					return 1;
			}
		}
	}
	return 0;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
		for(int j=0; j<C; j++) {
			if(arr[i][j] == '+')
				wood.push_back({i,j});
			else if(arr[i][j] == 'V')
				init = {i,j};
			else if(arr[i][j] == 'J')
				fin = {i,j};
		}
	}
	int l = 0, r = 1000, mid;
	while(l < r) {
		mid = (l+r+1)/2;
		if(ok(mid))
			l = mid;
		else
			r = mid-1;
	}
	cout << l;
}
