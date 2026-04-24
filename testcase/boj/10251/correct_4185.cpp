#include <bits/stdc++.h>
using namespace std;
int hor[100][100], ver[100][100], hdp[200][100][100], vdp[200][100][100];
void solve() {
	int m, n, l, g;
	cin >> n >> m >> l >> g;
	for(int i=0; i<n; i++) {
		for(int j=1; j<m; j++)
			cin >> hor[i][j];
	}
	for(int i=1; i<n; i++) {
		for(int j=0; j<m; j++)
			cin >> ver[i][j];
	}
	memset(vdp, 0x3f, sizeof vdp);
	memset(hdp, 0x3f, sizeof hdp);
	vdp[0][0][0] = hdp[0][0][0] = 0;
	for(int k=0; k<n+m; k++) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<m; j++) {
				if(i) {
					vdp[k][i][j] = vdp[k][i-1][j] + ver[i][j];
					if(k) {
						vdp[k][i][j] = min(vdp[k][i][j], hdp[k-1][i-1][j]+ver[i][j]);
					}
				}
				if(j) {
					hdp[k][i][j] = hdp[k][i][j-1] + hor[i][j];
					if(k)
						hdp[k][i][j] = min(hdp[k][i][j], vdp[k-1][i][j-1]+hor[i][j]);
				}
			}
		}
	}
	for(int k=1; k<n+m; k++) {
		if(min(hdp[k][n-1][m-1], vdp[k][n-1][m-1]) <= g) {
			cout << (k+(n+m-2)*l) << '\n';
			return;
		}
	}
	cout << "-1\n";
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--)
		solve();
}
