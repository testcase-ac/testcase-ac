#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
#define MAXN 100
int parentarr[MAXN*MAXN];
int n, m;
char arr[MAXN][MAXN+1];
int nextblock[MAXN*MAXN][4][2];
int offi[] = {-1,0,1,0}, offj[] = {0,1,0,-1};
inline int toX(int p){return p%m;}
inline int toY(int p){return p/m;}
int adj(int p, int dir) {
	switch(dir) {
		case 0:
			if(p < m) return -1;
			else return p - m;
		case 1:
			if(p % m == m-1) return -1;
			else return p+1;
		case 2:
			if(p+m >= n*m) return -1;
			else return p+m;
		case 3:
			if(p % m == 0) return -1;
			else return p-1;
	}
	return -1;
}
int parent(int i){return i == parentarr[i] ? i : parentarr[i] = parent(parentarr[i]);}
void joinroot(int i, int j){parentarr[i] = j;}
inline char color(int p) {
	return arr[p/m][p%m];
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n >> m;
	rep(i,n) cin >> arr[i];
	rep(i,n*m) parentarr[i] = i;
	for(int i=0; i<n*m; i++) {
		for(int d=0; d<4; d++) {
			int a = adj(i,d);
			if(a != -1 && color(i) == color(a))
				joinroot(parent(i), parent(a)); 
		}
	}
	map<int, vector<int>> conncomp;
	rep(i,n*m) conncomp[parent(i)].push_back(i);
	int tmp[4][2];
	auto settmp = [&tmp](int dp, int cc, int p) {
		int a = adj(p, dp);
		tmp[dp][cc] = ((a == -1 || color(a) == 'X') ? -1 : parent(a));
	};
	for(auto &pr: conncomp) {
		vector<int> &v = pr.second;
		sort(v.begin(), v.end()); // no comp: sort by y then x.
		int up = 1, down = sz(v)-2;
		while(up < sz(v) && toY(v[0]) == toY(v[up])) up++;
		while(down >= 0 && toY(v.back()) == toY(v[down])) down--;
		settmp(0,0,v[0]);
		settmp(0,1,v[up-1]);
		settmp(2,0,v.back());
		settmp(2,1,v[down+1]);
		sort(v.begin(), v.end(), [](int i, int j){
			return toX(i) == toX(j) ? toY(i) < toY(j) : toX(i) < toX(j);
		}); // sort by x then y
		int left = 0, right = sz(v)-2;
		while(left < sz(v) && toX(v[0]) == toX(v[left])) left++;
		while(right >= 0 && toX(v.back()) == toX(v[right])) right--;
		settmp(3,0,v[left-1]);
		settmp(3,1,v[0]);
		settmp(1,0,v[right+1]);
		settmp(1,1,v.back());
		memcpy(nextblock[pr.first], tmp, sizeof(tmp));
	}
	int pos = parent(0), dp = 1, cc = 0;
	while(1) {
		cout << color(pos);
		rep(i,4) {
			if(nextblock[pos][dp][cc] != -1) {
				pos = nextblock[pos][dp][cc];
				goto next;
			}
			cc ^= 1;
			if(nextblock[pos][dp][cc] != -1) {
				pos = nextblock[pos][dp][cc];
				goto next;
			}
			dp = (dp+1)%4;
		}
		return 0;
		next:;
	}
}
