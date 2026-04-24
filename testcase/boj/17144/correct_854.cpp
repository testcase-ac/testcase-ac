#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
int arr[50][50], tmp[50][50], dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1}, R, C;
vector<pii> cyc[2];
void f(pii a, pii b, vector<pii>& v) {
	while(a.first < b.first) {
		v.push_back(a);
		a.first++;
	}
	while(a.first > b.first) {
		v.push_back(a);
		a.first--;
	}
	while(a.second < b.second) {
		v.push_back(a);
		a.second++;
	}
	while(a.second > b.second) {
		v.push_back(a);
		a.second--;
	}
}
void build(pii a, pii b, pii c, pii d, vector<pii>& v) {
	f(a, b, v);
	f(b, c, v);
	f(c, d, v);
	f(d, a, v);
}
void rot(int t) {
	vector<pii>& v = cyc[t];
	for(int i=0; i<v.size(); i++) {
		int a, b, c, d;
		tie(a, b) = v[i];
		tie(c, d) = v[(i+1)%v.size()];
		tmp[c][d] = arr[a][b];
	}
}
void print() {
	cout << "Current:\n";
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T, rn;
	cin >> R >> C >> T;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			cin >> arr[i][j];
			if(arr[i][j] == -1)
				rn = i;
		}
	}
	build({rn, 0}, {rn, C-1}, {R-1, C-1}, {R-1, 0}, cyc[0]);
	rn--;
	build({rn, 0}, {rn, C-1}, {0, C-1}, {0, 0}, cyc[1]);
	while(T--) {
		memset(tmp, 0, sizeof tmp);
		for(int i=0; i<R; i++) {
			for(int j=0; j<C; j++) {
				if(arr[i][j] == -1) continue;
				int a = arr[i][j]/5;
				for(int t=0; t<4; t++) {
					int tr = i+dr[t], tc = j+dc[t];
					if(!(0 <= tr && tr < R && 0 <= tc && tc < C) || arr[tr][tc] == -1) continue;
					tmp[tr][tc] += a;
					arr[i][j] -= a;
				}
				tmp[i][j] += arr[i][j];
			}
		}
		memcpy(arr, tmp, sizeof arr);
		rot(0); rot(1); memcpy(arr, tmp, sizeof arr);
		arr[rn][0] = arr[rn+1][0] = -1;
	}
	int ans = 0;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			ans += arr[i][j];
		}
	}
	cout << ans+2;
}
