#include <bits/stdc++.h>
#pragma gcc optimize("O3")
#pragma gcc optimize("Ofast")
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair <int,int> pi;
typedef pair <ll,ll> pl;
int n,m,nx[4] = {1,0,-1,0},ny[4] = {0,1,0,-1};
char a[2005][2005];
ll g,mod = 1e9+7;

ll mpow(ll go) {
	if(!go) return 1LL;
	ll tmp = mpow(go/2);
	if(go % 2) return tmp*tmp*2LL%mod;
	return tmp*tmp%mod;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++) cin >> a[i]+1;
	int dx,dy;
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= m;j++) {
			g++;
			for(int k = 0;k < 4;k++) {
				dx = i+nx[k], dy = j+ny[k];
				if(dx < 1||dx > n||dy < 1||dy > m) continue;
				if(a[i][j] != a[dx][dy]) {
					g--;
					break;
				}
			}
		}
	}
	cout << mpow(g);
}