#include <bits/stdc++.h>
using namespace std;
char arr[25][26];
map<char, set<int>> mp;
set<int> ans;
int R, C, dr[] = {-1,0,1,0}, dc[] = {0,1,0,-1}, ar, ac;
int main() {
	mp['|'] = {0,2};
	mp['-'] = {1,3};
	mp['+'] = {0,1,2,3};
	mp['1'] = {1,2};
	mp['2'] = {0,1};
	mp['3'] = {0,3};
	mp['4'] = {2,3};
	cin >> R >> C;
	for(int i=0; i<R; i++)
		cin >> arr[i];
	for(int r=0; r<R; r++) {
		for(int c=0; c<C; c++) {
			char t = arr[r][c];
			if(t == '.' || isalpha(t)) continue;
			for(int i: mp[t]) {
				int tr = r+dr[i], tc = c+dc[i];
				if(arr[tr][tc] == '.') {
					ans.insert((i+2)%4);
					ar = tr, ac = tc;
				}
			}
		}
	}
	for(auto& pr: mp) {
		if(ans == pr.second)
			return !printf("%d %d %c", ar+1, ac+1, pr.first);
	}
}
