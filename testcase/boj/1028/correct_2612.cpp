#include <bits/stdc++.h>
using namespace std;
const int MX = 755;
char arr[MX][MX];
int R, C, tl[MX][MX], tr[MX][MX], bl[MX][MX], br[MX][MX], ans;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=1; i<=R; i++) {
        string s;
        cin >> s;
        for(int j=1; j<=C; j++) {
            arr[i][j] = s[j-1];
        }
	}
	for(int i=1; i<=R; i++) {
		for(int j=1; j<=C; j++) {
			if(arr[i][j] == '0') continue;
			tl[i][j] = tl[i-1][j-1]+1;
			tr[i][j] = tr[i-1][j+1]+1;
		}
	}
	for(int i=R; i>=1; i--) {
		for(int j=1; j<=C; j++) {
			if(arr[i][j] == '0') continue;
			bl[i][j] = bl[i+1][j-1]+1;
			br[i][j] = br[i+1][j+1]+1;
		}
	}
	for(int i=1; i<=R; i++) {
		for(int j=1; j<=C; j++) {
			for(int d=min({tr[i][j], br[i][j], (C-j)/2+1}); d>ans; d--) {
				int t = j+(d-1)*2;
				if(min(tl[i][t], bl[i][t]) >= d)
					ans = d;
			}
		}
	}
	cout << ans;
}
