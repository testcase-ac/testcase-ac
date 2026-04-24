#include <bits/stdc++.h>
using namespace std;
char arr[400][401];
int downto[400][400];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int r, c;
	cin >> r >> c;
	for(int i=0; i<r; i++) {
		cin >> arr[i];
	}
	for(int j=0; j<c; j++) {
		int lastx = r-1;
		for(int i=r-1; i>=0; i--) {
			if(arr[i][j] == 'X')
				lastx = i;
			downto[i][j] = lastx-1;
		}
	}
	int ans = 0;
	for(int i=0; i<r; i++) {
		for(int j=0; j<c; j++) {
			if(arr[i][j] == 'X') continue;
			int tr = i;
			while(tr && arr[tr-1][j] == '.')
				tr--;
			ans = max(ans, (i-tr+2)*2);
			for(int tc=j-1; tc>=0; tc--) {
				while(downto[tr][tc] < i && tr <= i)
					tr++;
				if(tr > i) break;
				ans = max(ans, (i-tr+j-tc+2)*2);
			}
		}
	}
	cout << ans-1;
}
