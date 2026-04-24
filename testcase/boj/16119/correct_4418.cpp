#include <bits/stdc++.h>
using namespace std;

/*
dp[k][i][j]: i,j at middle, width 2k+1: max (find k+1 size)
*/
int arr[2][1000][1000], ans[1000][1000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> arr[0][i][j];
			ans[i][j] = arr[0][i][j] - 1;
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			for(int a=max(0,i-1); a<min(n, i+2); a++) {
				for(int b=max(0,j-1); b<min(n, j+2); b++) {
					arr[1][i][j] = max(arr[1][i][j], arr[0][a][b]);
				}
			}
			ans[i][j] = max(ans[i][j], arr[1][i][j] - 4);
		}
	}
	int p, c;
	for(int k=2; k<=30; k++) {
		c = k&1, p = c^1;
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(i+1<n && j+1<n) arr[c][i][j] = max(arr[c][i][j], arr[p][i+1][j+1]);
				if(i+1<n && j-1>=0) arr[c][i][j] = max(arr[c][i][j], arr[p][i+1][j-1]);
				if(i-1>=0 && j+1<n) arr[c][i][j] = max(arr[c][i][j], arr[p][i-1][j+1]);
				if(i-1>=0 && j-1>=0) arr[c][i][j] = max(arr[c][i][j], arr[p][i-1][j-1]);
				ans[i][j] = max(ans[i][j], arr[c][i][j] - (k+1)*(k+1));
			}
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cout << ans[i][j] << ' ';
		}
		cout << '\n';
	}

}
