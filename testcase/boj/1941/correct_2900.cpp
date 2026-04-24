#include <bits/stdc++.h>
using namespace std;

char arr[5][6];
bool seen[5][5];
int di[] = {1,-1,0,0}, dj[] = {0,0,1,-1}, ans;
bool ok(int i, int j) {return 0 <= i && i < 5 && 0 <= j && j < 5;}
vector<int> v;
pair<int, int> dfs(int i, int j) {
	seen[i][j] = 1;
	int cnt = 1, cnts = arr[i][j] == 'S';
	for(int t=0; t<4; t++) {
		int ti = i+di[t], tj = j+dj[t];
		if(ok(ti, tj) && !seen[ti][tj] && binary_search(v.begin(), v.end(), ti*5+tj)) {
			auto pr = dfs(ti, tj);
			cnt += pr.first, cnts += pr.second;
		}
	}
	return {cnt, cnts};
}
void f(int i) {
	v.push_back(i);
	if(v.size() == 7) {
		memset(seen, 0, sizeof seen);
		auto pr = dfs(v[0]/5, v[0]%5);
		if(pr.first == 7 && pr.second >= 4)
			ans++;
	} else {
		for(int j=i+1; j+7-v.size()<=25; j++)
			f(j);
	}
	v.pop_back();
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=0; i<5; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<=18; i++)
		f(i);
	cout << ans;
}
