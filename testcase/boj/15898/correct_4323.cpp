#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int tx[4][4];
char tc[4][4];
struct Material {
	int x[4][4];
	char c[4][4];
	void rotate() {
		memcpy(tx, x, sizeof(tx));
		memcpy(tc, c, sizeof(tc));
		rep(i,4) rep(j,4) {
			x[j][3-i] = tx[i][j];
			c[j][3-i] = tc[i][j];
		}
	}
};
pair<int, int> disp[] = {{0,0}, {0,1}, {1,0}, {1,1}};
struct Gama {
	int x[5][5];
	char c[5][5];
	void apply(Material &m, pair<int, int> d) {
		int a = d.first, b = d.second;
		rep(i,4) rep(j,4) {
			x[a+i][b+j] += m.x[i][j];
			if(x[a+i][b+j] > 9) x[a+i][b+j] = 9;
			if(x[a+i][b+j] < 0) x[a+i][b+j] = 0;
			if(m.c[i][j] != 'W') c[a+i][b+j] = m.c[i][j];
		}
	}
	void reset() {
		memset(x, 0, sizeof(x));
		memset(c, 0, sizeof(c));
	}
	int res(Material &m1, Material &m2, Material &m3) {
		int ret = 0;
		rep(i,4) rep(j,4) rep(k,4) {
			reset();
			apply(m1, disp[i]);
			apply(m2, disp[j]);
			apply(m3, disp[k]);
			int r = 0, b = 0, g = 0, y = 0;
			rep(l,5) rep(m,5) {
				if(c[l][m] == 'R') r += x[l][m];
				else if(c[l][m] == 'B') b += x[l][m];
				else if(c[l][m] == 'G') g += x[l][m];
				else if(c[l][m] == 'Y') y += x[l][m];
			}
			ret = max(ret, 7*r+5*b+3*g+2*y);
		}
		return ret;
	}
};

Material m[10][4];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	rep(i,n) {
		rep(j,4) rep(k,4) cin >> m[i][0].x[j][k];
		rep(j,4) rep(k,4) cin >> m[i][0].c[j][k];
	}
	rep(i,n) {
		for(int j=1; j<4; j++) {
			m[i][j] = m[i][j-1];
			m[i][j].rotate();
		}
	}
	int ans = 0;
	Gama g;
	rep(i,n) rep(j,n) rep(k,n) {
		if(i == j || i == k || j == k) continue;
		rep(a,4) rep(b,4) rep(c,4)
			ans = max(ans, g.res(m[i][a], m[j][b], m[k][c]));
	}
	cout << ans;
}
