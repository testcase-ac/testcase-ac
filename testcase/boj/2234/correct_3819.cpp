#include <bits/stdc++.h>
using namespace std;
int par[2500], setsz[2500], setcnt, maxsz=1, rmsz, a, b, C, R;
int find(int i) {return i == par[i] ? i : par[i] = find(par[i]);}
void join(int i, int j) {
	i = find(i), j = find(j);
	if(i != j) {
		par[i] = j;
		setsz[j] += setsz[i];
		maxsz = max(maxsz, setsz[j]);
		setcnt--;
	}
}
int main() {
	cin >> C >> R;
	for(int i=0; i<C*R; i++) {
		par[i] = i;
		setsz[i] = 1;
	}
	setcnt = C*R;
	vector<pair<int, int>> walls;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			int t;
			cin >> t;
			if((t&1) && j)
				walls.push_back({i*C+j, i*C+j-1});
			else if(j)
				join(i*C+j, i*C+j-1);
			if((t&2) && i)
				walls.push_back({i*C+j, (i-1)*C+j});
			else if(i)
				join(i*C+j, (i-1)*C+j);				
		}
	}
	for(auto w: walls) {
		tie(a,b) = w;
		a = find(a), b = find(b);
		if(a != b) rmsz = max(rmsz, setsz[a]+setsz[b]);
	}
	printf("%d\n%d\n%d", setcnt, maxsz, rmsz);
}
