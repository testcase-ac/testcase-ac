#include <bits/stdc++.h>
using namespace std;

char arr[250][251];
int R, C, dr[]={1,-1,0,0}, dc[]={0,0,1,-1},a,b;
pair<int, int> dfs(int r, int c) {
	pair<int, int> ret = {0,0};
	if(arr[r][c] == 'o')
		ret = {1,0};
	else if(arr[r][c] == 'v')
		ret = {0,1};
	arr[r][c] = '#';
	for(int i=0; i<4; i++) {
		int tr = r+dr[i], tc = c+dc[i];
		if(0 <= tr && tr < R && 0 <= tc && tc < C && arr[tr][tc] != '#') {
			auto res = dfs(tr, tc);
			ret.first += res.first;
			ret.second += res.second;
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(arr[i][j] != '#') {
				auto pr = dfs(i, j);
				if(pr.first > pr.second)
					a += pr.first;
				else
					b += pr.second;
			}
		}
	}
	cout << a << ' ' << b;
}
